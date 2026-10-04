
#include "sim/motions/BraitenbergMotion.h"

#include <iostream>

BraitenbergMotion::BraitenbergMotion(std::string motionType, double arenaWidth,
                                     double arenaHeight,
                                     const nlohmann::json& data,
                                     GenericSensor* leftSensor,
                                     GenericSensor* rightSensor)
    : Motion(motionType), leftSensor(leftSensor), rightSensor(rightSensor) {
  if (motionType == "explore") {
    motion = new Explore(arenaWidth, arenaHeight, data);
    // std::cout << "GOT TO BMotion spot" << std::endl;
  } else if (motionType == "love") {
    motion = new Love(arenaWidth, arenaHeight, data);
  } else if (motionType == "aggression") {
    motion = new Aggression(arenaWidth, arenaHeight, data);
  } else if (motionType == "fear") {
    motion = new Fear(arenaWidth, arenaHeight, data);
  }
}

BraitenbergMotion::~BraitenbergMotion() {
  delete motion;
  delete leftSensor;
  delete rightSensor;
}

void BraitenbergMotion::Update(double dt, Vector3& pos, Vector3& vel,
                               Vector3& dir) {
  leftSensor->Update(pos, dir);
  rightSensor->Update(pos, dir);
  double leftVal = leftSensor->GetSensorValue();
  double rightVal = rightSensor->GetSensorValue();
  motion->SetSensorValues(leftVal, rightVal);
  motion->Update(dt, pos, vel, dir);
}