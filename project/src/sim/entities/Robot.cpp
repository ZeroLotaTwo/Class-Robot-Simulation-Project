/**
 * @file Robot.cpp
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#define _USE_MATH_DEFINES
#include "sim/entities/Robot.h"

#include <algorithm>
#include <cmath>

Robot::Robot(Motion* movement, Vector3 pos, Vector3 dir, double radius,
             const json& data) {
  // Set the type and the type name of the entity. (Do this with all entities)
  SetType<Robot>("Robot");
  json motion = data.value("motion", json::object());
  // Initialize motion variables
  this->speed = motion.value("speed", 0.0);
  this->motion = motion.value("type", "default");
  this->movement = movement;
  // Set the type and the type name of the entityd. (Do this with all entities)
  SetType<Robot>("Robot");
  this->pos = pos;
  this->dir = dir;
  this->radius = radius;

  // Energy capacity (variable at creation); optional initial charge
  maxCharge = 100.0;
  if (motion.contains("battery")) {
    maxCharge = motion["battery"].get<double>();
  } else if (motion.contains("maxCharge")) {
    maxCharge = motion["maxCharge"].get<double>();
  } else if (motion.contains("capacity")) {
    maxCharge = motion["capacity"].get<double>();
  }
  charge = maxCharge;
  if (motion.contains("charge")) {
    charge = motion["charge"].get<double>();
    if (charge > maxCharge) {
      charge = maxCharge;
    }
    if (charge < 0.0) {
      charge = 0.0;
    }
  }

  // Initialize motion variables
  if (motion.contains("speed")) {
    this->speed = motion["speed"];
  } else {
    this->speed = 0.0;
  }

  vel = dir * speed;
}

#include <iostream>

void Robot::Update(double dt) {
  if (GetCharge() <= 0.0) {
    return;  // Robot out of energy, can't move
  }
  const Vector3 oldPos = pos;
  movement->Update(dt, pos, vel, dir);
  DrainEnergyForMovement(dt, oldPos, pos);
}

void Robot::AddCharge(double amount) {
  charge = std::clamp(charge + amount, 0.0, maxCharge);
}

void Robot::DrainCharge(double amount) {
  charge = std::clamp(charge - amount, 0.0, maxCharge);
}

void Robot::DrainEnergyForMovement(double dt, const Vector3& oldPos,
                                   const Vector3& newPos) {
  const double dx = newPos[0] - oldPos[0];
  const double dy = newPos[1] - oldPos[1];
  const double dz = newPos[2] - oldPos[2];
  const double horizontal_distance = std::sqrt(dx * dx + dy * dy);
  const double positive_vertical_distance = std::max(0.0, dz);
  const double negative_vertical_distance = std::max(0.0, -dz);
  const double cost = (horizontal_distance + 10.0 * positive_vertical_distance +
                       0.1 * negative_vertical_distance + 0.01) *
                      dt * (radius / 50.0) * 15;
  charge = std::clamp(charge - cost, 0.0, maxCharge);
}
