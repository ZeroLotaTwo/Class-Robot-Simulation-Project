#include "sim/motions/SimpleMotions/KeyboardMotion.h"

#include <iostream>

KeyboardMotion::KeyboardMotion(double arenaWidth, double arenaHeight,
                               const nlohmann::json& data) {
  nlohmann::json motion = data.value("motion", nlohmann::json::object());
  speed = motion.value("speed", 0.0);
  this->arenaWidth = arenaWidth;
  this->arenaHeight = arenaHeight;
  radius = data.value("radius", 0.0);
  std::vector<std::string> keys =
      motion.value("keys", std::vector<std::string>{"w", "d", "s", "a"});
  keyUp = keys[0];
  keyRight = keys[1];
  keyDown = keys[2];
  keyLeft = keys[3];
}

void KeyboardMotion::Update(double dt, Vector3& pos, Vector3& vel,
                            Vector3& dir) {
  Vector3 newVel(0, 0, 0);

  if (pressedKeys.find(keyUp) != pressedKeys.end()) {
    newVel[1] += speed;
  }
  if (pressedKeys.find(keyDown) != pressedKeys.end()) {
    newVel[1] -= speed;
  }
  if (pressedKeys.find(keyLeft) != pressedKeys.end()) {
    newVel[0] -= speed;
  }
  if (pressedKeys.find(keyRight) != pressedKeys.end()) {
    newVel[0] += speed;
  }

  // Update velocity based on pressed keys (2D only: z stays 0)
  if (newVel.Length() > 0) {
    vel = newVel.Normalized() * speed;
    vel[2] = 0;
  } else {
    vel[0] = 0;
    vel[1] = 0;
    vel[2] = 0;
  }

  pos = pos + vel * dt;
  pos[2] = 0;

  // Wall collisions
  if (pos[0] > arenaWidth - radius || pos[1] > arenaHeight - radius ||
      pos[0] < radius || pos[1] < radius) {
    pos = pos - vel * dt;
    pos[2] = 0;
    vel[0] = 0;
    vel[1] = 0;
    vel[2] = 0;
  }

  // Update direction and speed based on velocity
  if (vel.Length() > 0) {
    dir = vel.Normalized();
  }
}

void KeyboardMotion::KeyDown(const std::string& key) {
  pressedKeys.insert(key);
}

void KeyboardMotion::KeyUp(const std::string& key) { pressedKeys.erase(key); }