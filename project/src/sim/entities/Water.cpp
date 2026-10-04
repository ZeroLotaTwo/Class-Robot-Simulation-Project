#include "sim/entities/Water.h"

Water::Water(Motion* movement, Vector3 pos, Vector3 dir, double radius,
             const json& data) {
  SetType<Water>("water");

  this->pos = pos;
  this->radius = radius;
  this->dir = dir;

  json motion = data.value("motion", json::object());
  this->speed = motion.value("speed", 0.0);
  this->motion = motion.value("type", "default");

  vel = dir * speed;
  this->movement = movement;
}

void Water::Update(double dt) { movement->Update(dt, pos, vel, dir); }

Water::~Water() {}