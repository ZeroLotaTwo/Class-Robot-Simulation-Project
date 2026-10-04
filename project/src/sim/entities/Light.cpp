/**
 * @file Light.cpp
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#define _USE_MATH_DEFINES
#include "sim/entities/Light.h"

#include <algorithm>
#include <cmath>
#include <iostream>

Light::Light(Motion* movement, Vector3 pos, Vector3 dir, double radius,
             const json& data) {
  SetType<Light>("Light");
  this->pos = pos;
  this->radius = radius;
  this->dir = dir;
  json motion = data.value("motion", json::object());
  this->speed = motion.value("speed", 0.0);
  this->motion = motion.value("type", "default");
  vel = dir * speed;
  this->movement = movement;
}

Light::~Light() {}

double Light::GetIntensity() const {
  if (radius <= 1e-9) {
    return 0.0;
  }
  return 100.0 / radius;
}

void Light::Update(double dt) { movement->Update(dt, pos, vel, dir); }
