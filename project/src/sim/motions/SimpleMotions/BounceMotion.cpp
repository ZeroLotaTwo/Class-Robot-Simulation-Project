#include "sim/motions/SimpleMotions/BounceMotion.h"

#include <iostream>
BounceMotion::BounceMotion(double arenaWidth, double arenaHeight,
                           const nlohmann::json& data)
    : arenaWidth(arenaWidth), arenaHeight(arenaHeight) {
  nlohmann::json motion = data.value("motion", nlohmann::json::object());
  speed = motion.value("speed", 0.0);
  radius = data.value("radius", 0.0);
  std::vector<double> velTemp =
      motion.value("initial_velocity", std::vector<double>{0, 0, 0});
}

void BounceMotion::Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir) {
  Vector3 n(0, 0, 0);
  bool collided = false;

  // Check Wall Boundaries
  if (pos[0] > arenaWidth - radius) {
    pos[0] = arenaWidth - radius;
    n = Vector3(-1, 0, 0);
    collided = true;
  } else if (pos[0] < radius) {
    pos[0] = radius;
    n = Vector3(1, 0, 0);
    collided = true;
  } else if (pos[1] > arenaHeight - radius) {
    pos[1] = arenaHeight - radius;
    n = Vector3(0, -1, 0);
    collided = true;
  } else if (pos[1] < radius) {
    pos[1] = radius;
    n = Vector3(0, 1, 0);
    collided = true;
  }

  // Apply bouncing formula: v' = v - 2(dot(n,v)*n)
  if (collided) {
    vel -= (n * (vel * n)) * 2;
    vel = vel.Normalized();
    if (vel.Length() > 0) {
      vel = vel.Normalized();
      dir = vel;
    }
    vel = vel * speed;
  }
  pos = pos + vel * dt;
  return;
}