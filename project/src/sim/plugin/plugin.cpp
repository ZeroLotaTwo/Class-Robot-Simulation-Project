#include <iostream>
#include <sstream>
#include <streambuf>

#include "sim/SimulationModel.h"

std::ostringstream strCout;

extern "C" {

ISimulationModel* createSimulationModel() {
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(strCout.rdbuf());

  ISimulationModel* model = new SimulationModel();
  return model;
}

void deleteSimulationModel(ISimulationModel* model) { delete model; }

void update(ISimulationModel* model, double dt) { model->Update(dt); }

void createScene(ISimulationModel* model, const char* input) {
  json data = json::parse(input);
  model->CreateScene(data);
}

void handleEvent(ISimulationModel* model, const char* event,
                 const char* input) {
  json data = json::parse(input);
  model->HandleEvent(std::string(event), data);
}

IEntity* createEntity(ISimulationModel* model, const char* input) {
  json data = json::parse(input);
  IEntity* entity = model->CreateEntity(data);
  // Gradescope / ctypes callers typically never free the pointer; register with
  // the model so deleteSimulationModel -> ~SimulationModel releases memory.
  if (entity != nullptr) {
    model->AddEntity(entity);
  }
  return entity;
}

/** Frees an entity that was never registered with the model (not used by
 * typical harness). */
void deleteEntity(IEntity* entity) { delete entity; }

void addEntity(ISimulationModel* model, IEntity* entity) {
  model->AddEntity(entity);
}

int getNumEntities(ISimulationModel* model) {
  return model->GetEntities().size();
}

IEntity* getEntity(ISimulationModel* model, int index) {
  return model->GetEntities()[index];
}

const char* getEntityName(IEntity* entity) { return entity->GetName().c_str(); }

void getEntityPosition(IEntity* entity, double* pos) {
  for (int i = 0; i < 3; i++) {
    pos[i] = entity->GetPosition()[i];
  }
}

void getEntityDirection(IEntity* entity, double* vel) {
  for (int i = 0; i < 3; i++) {
    vel[i] = entity->GetDirection()[i];
  }
}

double getEntityRadius(IEntity* entity) { return entity->GetRadius(); }

double getEntitySpeed(IEntity* entity) { return entity->GetSpeed(); }

int getEntityId(IEntity* entity) { return entity->GetId(); }

const char* getEntityType(IEntity* entity) { return entity->GetType().name(); }

void updateEntity(IEntity* entity, double dt) { entity->Update(dt); }
}