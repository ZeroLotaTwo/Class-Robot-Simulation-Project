#include "sim/sensors/GenericSensor.h"

GenericSensor::GenericSensor(std::string entityTarget, int entityId,
                             const ISimulationModel& arena, Vector3 pos,
                             Vector3 dir, double radiusAway, double angle)
    : Sensor(arena, pos, dir, radiusAway, angle),
      entityId(entityId),
      entityTarget(entityTarget) {}

GenericSensor::~GenericSensor() {}

void GenericSensor::Update(Vector3 entityNewPos, Vector3 entityNewDir) {
  this->CalcSensorPos(entityNewPos, entityNewDir);
  this->dir = entityNewDir;
}

double GenericSensor::GetDist() {
  if (entityTarget == "light")
    return GetGenericDist<Light>();
  else if (entityTarget == "robot")
    return GetGenericDist<Robot>();
  else if (entityTarget == "predator")
    return GetGenericDist<Predator>();
  else if (entityTarget == "bv")
    return GetGenericDist<BraitenbergVehicle>();
  else if (entityTarget == "water")
    return GetGenericDist<Water>();
  else if (entityTarget == "energy")
    return GetGenericDist<EnergyEntity>();
  else
    return GetGenericDist<EntityBase>();
}

EntityBase* GenericSensor::GetClosestGeneric() {
  if (entityTarget == "light")
    return GetClosestGeneric<Light>();
  else if (entityTarget == "robot")
    return GetClosestGeneric<Robot>();
  else if (entityTarget == "predator")
    return GetClosestGeneric<Predator>();
  else if (entityTarget == "bv")
    return GetClosestGeneric<BraitenbergVehicle>();
  else if (entityTarget == "water")
    return GetClosestGeneric<Water>();
  else if (entityTarget == "energy")
    return GetClosestGeneric<EnergyEntity>();
  else
    return GetClosestGeneric<EntityBase>();
}

double GenericSensor::GetSensorValue() {
  double minDistance = GetDist();
  return std::max(1800.0 / std::pow(1.08, minDistance), 0.0001);
}