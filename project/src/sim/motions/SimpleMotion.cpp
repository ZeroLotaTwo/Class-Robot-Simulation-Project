#include "sim/motions/SimpleMotion.h"

#include <iostream>

SimpleMotion::SimpleMotion(std::string motionType, double arenaWidth,
                           double arenaHeight, const nlohmann::json& data)
    : Motion(motionType) {
  if (motionType == "back_and_forth") {
    motion = new BackAndForth(data);
  } else if (motionType == "around") {
    motion = new Around(data);
  } else if (motionType == "keyboard") {
    motion = new KeyboardMotion(arenaWidth, arenaHeight, data);
  } else if (motionType == "bounce") {
    motion = new BounceMotion(arenaWidth, arenaHeight, data);
  } else {
    motion = new DefaultMotion();
  }
}

SimpleMotion::~SimpleMotion() { delete motion; }

void SimpleMotion::Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir) {
  motion->Update(dt, pos, vel, dir);
}

IndividualMotionI* SimpleMotion::GetMotion() const { return motion; }