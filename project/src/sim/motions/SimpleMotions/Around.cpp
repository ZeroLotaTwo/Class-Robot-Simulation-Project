#include "sim/motions/SimpleMotions/Around.h"

#include <iostream>

Around::Around(const nlohmann::json& data) {
  nlohmann::json motion = data.value("motion", nlohmann::json::object());

  speed = motion.value("speed", 0.0);

  std::vector<double> center =
      motion.value("center", std::vector<double>{0, 0, 0});
  this->rotation_center = Vector3(center[0], center[1], center[2]);

  std::vector<double> startingSpotTemp =
      data.value("position", std::vector<double>{0, 0, 0});
  Vector3 startingSpot =
      Vector3(startingSpotTemp[0], startingSpotTemp[1], startingSpotTemp[2]);
  Vector3 offset = startingSpot - rotation_center;

  this->rotation_radius = offset.Length();
  this->angle = std::atan2(offset[1], offset[0]);

  std::string direction = motion.value("direction", "clockwise");
  counterclockwise = (direction == "counterclockwise");
}

void Around::Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir) {
  // update angle using angular speed and uses it to reset position
  double omega = speed / rotation_radius;
  // clockwise = negative direction in standard math coords
  if (counterclockwise) {
    angle += omega * dt;
  } else {
    angle -= omega * dt;
  }

  // regulate angle variable
  if (angle > M_PI) angle -= 2 * M_PI;
  if (angle < -M_PI) angle += 2 * M_PI;

  // move
  pos[0] = rotation_center[0] + rotation_radius * std::cos(angle);
  pos[1] = rotation_center[1] + rotation_radius * std::sin(angle);
}
