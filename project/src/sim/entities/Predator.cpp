#include "sim/entities/Predator.h"

#include <iostream>

#include "sim/sensors/GenericSensor.h"

Predator::Predator(Motion* movement, Motion* attack, GenericSensor* sensor,
                   Vector3 pos, Vector3 dir, double radius, const json& data)
    : Robot(movement, pos, dir, radius, data), attack(attack), sensor(sensor) {
  // disguise is optional; operator[] aborts in debug if the key is missing.
  falseType = data.value("disguise", json::object())
                  .value("type", std::string("predator"));
  SetFalseType();
}
void Predator::SetFalseType() {
  if (falseType == "energy") {
    SetType<EnergyEntity>(falseType);
  } else if (falseType == "light") {
    ;
    SetType<Light>(falseType);
  } else if (falseType == "BraitenbergVehicle") {
    SetType<BraitenbergVehicle>(falseType);
  } else if (falseType == "robot") {
    SetType<Robot>(falseType);
  } else if (falseType == "water") {
    SetType<Water>(falseType);
  } else {
    SetType<Predator>(falseType);
  }
}
Predator::~Predator() {
  delete sensor;
  delete attack;
}

bool Predator::CanDrainEnergy() {
  double dist = sensor->GetDist();
  if (dist == -1) {
    return false;
  }
  return dist < 0.000001;
}

void Predator::DrainClosestRobotEnergy() {
  EntityBase* closestEnt = sensor->GetClosestGeneric();
  Robot* closestRobot = dynamic_cast<Robot*>(closestEnt);
  if (closestRobot) {
    double chargeAmt = closestRobot->GetCharge();
    this->AddCharge(chargeAmt);
    closestRobot->DrainCharge(chargeAmt);
  }
}

void Predator::Update(double dt) {
  // motion.update(pos, dir, speed, dt);
  if (CanDrainEnergy()) {
    DrainClosestRobotEnergy();
  }
  if (sensor->GetDist() <= radius) {
    if (!motionSwaped) {
      Motion* temp = movement;
      movement = attack;
      attack = temp;
      SetType<Predator>("predator");
      motionSwaped = true;
    }
  } else {
    if (motionSwaped) {
      Motion* temp = movement;
      movement = attack;
      attack = temp;
      SetFalseType();
      motionSwaped = false;
    }
  }
  Robot::Update(dt);
  sensor->Update(pos, dir);
}

Vector3 Predator::GetPos() { return pos; }
Vector3 Predator::GetDir() { return dir; }
Vector3 Predator::GetVel() { return vel; }
