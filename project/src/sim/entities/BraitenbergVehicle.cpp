/**
 * @file BraitenbergVehicle.cpp
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#include "sim/entities/BraitenbergVehicle.h"

#include "sim/sensors/GenericSensor.h"

BraitenbergVehicle::BraitenbergVehicle(Motion* movement,
                                       GenericSensor* leftSensor,
                                       GenericSensor* rightSesor, Vector3 pos,
                                       Vector3 dir, double radius,
                                       const json& data)
    : Robot(movement, pos, dir, radius, data),
      leftSensor(leftSensor),
      rightSensor(rightSesor) {
  maxSpeed = 0.0;  // safe default
  auto motion = data.value("motion", json::object());
  if (motion.is_object()) {
    maxSpeed = motion.value("speed", 0.0);
  }
}

double BraitenbergVehicle::GetLeftLightSensorValue() {
  return leftSensor->GetSensorValue();
}
double BraitenbergVehicle::GetRightLightSensorValue() {
  return rightSensor->GetSensorValue();
}

void BraitenbergVehicle::Update(double dt) { Robot::Update(dt); }

BraitenbergVehicle::~BraitenbergVehicle() {}
