/**
 * @file SimulationModel.cpp
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#include "sim/SimulationModel.h"

#include <iostream>

#include "sim/entities/Water.h"

/**
 * Recharge rate while overlapping: d(charge) = dt * intensity / 5
 * (empty to full in 5 s when intensity matches capacity — see spec).
 */
EnergyEntity* GetClosestEnergy(const std::vector<IEntity*>* entities,
                               const Vector3& pos) {
  if (entities->size() < 1) {
    return nullptr;
  }
  // Since you can't have negative distance. We can have a sentinal value
  double minDistance = -1;
  EnergyEntity* closestEnergy = nullptr;
  for (auto entity : *entities) {
    EnergyEntity* curEnergy = dynamic_cast<EnergyEntity*>(entity);
    if (curEnergy == NULL) {
      continue;
    }
    Vector3 EnergyPos = Vector3(curEnergy->GetPosition());
    double curDist = (EnergyPos - (pos)).Length();
    if (curDist < minDistance || minDistance == -1) {
      minDistance = curDist;
      closestEnergy = curEnergy;
    }
  }
  return closestEnergy;
}

void ApplyRobotEnergyRecharge(double dt,
                              const std::vector<IEntity*>& entities) {
  for (IEntity* e : entities) {
    Robot* robot = e->AsType<Robot>();
    if (robot == nullptr) {
      continue;
    }
    Vector3 rp = Vector3(robot->GetPosition());
    const EnergyEntity* best = GetClosestEnergy(&entities, Vector3(rp));
    if (best == nullptr) {
      continue;
    }
    Vector3 bestPos = Vector3(best->GetPosition());
    double bestDist = (rp - bestPos).Length();

    if (best->CanIdentifyAsEnergy(bestDist)) {
      robot->AddCharge(dt * best->GetIntensity() / 5.0);
    }
  }
}

SimulationModel::SimulationModel() {}

SimulationModel::~SimulationModel() {
  for (IEntity* entity : entities) {
    delete entity;
  }
  entities.clear();
}

json SimulationModel::CreateScene(const json& data) {
  json returnVal = data;
  width = returnVal["width"];
  height = returnVal["height"];
  json& entities = returnVal["entities"];
  for (int i = 0; i < entities.size(); i++) {
    IEntity* entity = CreateEntity(entities[i]);
    int id = -1;
    if (entity) {
      AddEntity(entity);
      id = entity->GetId();
    }
    entities[i]["id"] = id;
  }

  return returnVal;
}

double count = 0;
void SimulationModel::Update(double dt) {
  // if(count > 1){
  //   return;
  // }
  for (int i = 0; i < GetEntities().size(); i++) {
    IEntity* entity = GetEntities()[i];
    entity->Update(dt);
  }
  ApplyRobotEnergyRecharge(dt, entities);
  ApplyRobotWaterDrain(dt);
  // count += dt;
  // std::cout << dt << std::endl;
}

IEntity* SimulationModel::CreateEntity(const json& data) const {
  EntityBase* newEntity = nullptr;
  Predator* newPred = nullptr;
  json motion = data.value("motion", json::object());
  json pos = data.value("position", json({0, 0, 0}));
  json dir = data.value("direction", json({0, 0, 0}));
  Vector3 posV(pos[0], pos[1], pos[2]);
  Vector3 dirV = Vector3(dir[0], dir[1], dir[2]).Normalized();
  if (data["type"] == "robot") {
    newEntity = new Robot(nullptr, Vector3(pos[0], pos[1], pos[2]),
                          Vector3(dir[0], dir[1], dir[2]).Normalized(),
                          data["radius"], data);

  } else if (data["type"] == "bv") {
    newEntity = new BraitenbergVehicle(nullptr, nullptr, nullptr, posV, dirV,
                                       data["radius"], data);

  } else if (data["type"] == "light") {
    newEntity = new Light(nullptr, posV, dirV, data["radius"], data);
  }
  if (data["type"] == "energy") {
    newEntity = new EnergyEntity(nullptr, posV, dirV, data["radius"], data);
  }

  if (data["type"] == "water") {
    newEntity = new Water(nullptr, posV, dirV, data["radius"], data);
  }
  if (data["type"] == "predator") {
    newPred = new Predator(nullptr, nullptr, nullptr, posV, dirV,
                           data["radius"], data);
    newEntity = ConvertPred(newPred, data).ConvertToEntity();
    int curEntityId = newEntity->GetId();
    GenericSensor* robotSensor =
        new GenericSensor("robot", curEntityId, *this, posV, dirV, 0, 0);
    GenericSensor* leftAttack = new GenericSensor(
        "robot", curEntityId, *this, (posV), (dirV), data["radius"], 40);
    GenericSensor* rightAttack = new GenericSensor(
        "robot", curEntityId, *this, (posV), (dirV), data["radius"], -40);
    Motion* attackMovement = new BraitenbergMotion(
        "aggression", width, height, data, leftAttack, rightAttack);
    newPred->attack = attackMovement;
    newPred->sensor = robotSensor;
  }
  std::string motionType =
      motion.value("behavior", motion.value("type", "N/A"));
  GenericSensor* leftSensor = nullptr;
  GenericSensor* rightSensor = nullptr;
  Motion* movement = nullptr;
  if (!newEntity) {
    return nullptr;
  }
  int curEntityId = newEntity->GetId();
  if (motionType == "fear" || motionType == "explore" || motionType == "love" ||
      motionType == "aggression") {
    std::string entityTarget = motion.value("target", "light");
    leftSensor = new GenericSensor(entityTarget, curEntityId, *this, posV, dirV,
                                   data["radius"], 40);
    rightSensor = new GenericSensor(entityTarget, curEntityId, *this, posV,
                                    dirV, data["radius"], -40);
    movement = new BraitenbergMotion(motionType, width, height, data,
                                     leftSensor, rightSensor);
  } else {
    motionType = data.value("motion", json::object()).value("type", "default");
    movement = new SimpleMotion(motionType, width, height, data);
  }
  newEntity->movement = movement;
  newEntity->motion = motionType;
  if (newPred) {
    newPred->movement = movement;
    newPred->motion = motionType;
  }
  if (data["type"] == "bv") {
    BraitenbergVehicle* tempBV = dynamic_cast<BraitenbergVehicle*>(newEntity);
    tempBV->leftSensor = leftSensor;
    tempBV->rightSensor = rightSensor;
  }
  return newEntity;
}

void SimulationModel::AddEntity(IEntity* entity) { entities.push_back(entity); }

void SimulationModel::HandleEvent(const std::string& event, const json& data) {
  if (event == "KeyUp" || event == "KeyDown") {
    std::string key = data["key"].get<std::string>();
    for (IEntity* entity : GetEntities()) {
      EntityBase* ent = dynamic_cast<EntityBase*>(entity);
      if (!ent) continue;
      if (ent->motion != "keyboard") continue;

      SimpleMotion* sm = dynamic_cast<SimpleMotion*>(ent->movement);
      if (!sm) continue;

      KeyboardMotion* km = dynamic_cast<KeyboardMotion*>(sm->GetMotion());
      if (!km) continue;

      if (event == "KeyDown") {
        km->KeyDown(key);
      } else {
        km->KeyUp(key);
      }
    }
  }
}

void SimulationModel::ApplyRobotWaterDrain(double dt) {
  for (IEntity* ent : entities) {
    Robot* robot = ent->AsType<Robot>();
    if (!robot) continue;

    for (IEntity* other : entities) {
      Water* water = dynamic_cast<Water*>(other);
      if (!water) continue;

      double dist =
          (Vector3(robot->GetPosition()) - Vector3(water->GetPosition()))
              .Length();
      if (dist <= (robot->GetRadius() + water->GetRadius())) {
        robot->DrainCharge(robot->GetMaxCharge() * 0.1 * dt);
        printf("DRONE IN WATER - CHARGE: %f\n", robot->GetCharge());
      }
    }
  }
}
