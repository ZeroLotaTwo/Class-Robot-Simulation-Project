#include "sim/motions/BraitenbergMotions/Explore.h"

#include <iostream>
Explore::Explore(double arenaWidth, double arenaHeight,
                 const nlohmann::json& data)
    : arenaWidth(arenaWidth), arenaHeight(arenaHeight) {
  nlohmann::json motion = data.value("motion", nlohmann::json::object());
  double radius = motion.value("radius", 0.0);
  kinematics.SetRadius(radius);
  this->radius = radius;
  maxSpeed = motion.value("speed", motion.value("maxSpeed", 100.0));
}

// void Explore::SetSensorValues(double leftValue, double rightValue){
//     this->leftVal = leftValue;
//     this->rightVal = rightValue;
// }

void Explore::Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir) {
  double leftWheelVelocity = std::min(1.0 / rightVal, maxSpeed);
  double rightWheelVelocity = std::min(1.0 / leftVal, maxSpeed);
  vel = dir * speed;
  kinematics.SetPosition(pos);
  kinematics.SetDirection(dir);
  kinematics.Update(dt, leftWheelVelocity, rightWheelVelocity, pos, vel);
  dir = vel.Normalized();
  speed = vel.Length();

  //
  if (pos[0] < radius || pos[1] < radius || pos[0] + radius > arenaWidth ||
      pos[1] + radius > arenaHeight) {
    dir = dir * -1.0;
  }
}
