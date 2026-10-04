/**
 * @file DifferentialDriveMotion.cpp
 */

#include "sim/physics/DifferentialDriveMotion.h"

DifferentialDriveMotion::DifferentialDriveMotion(double radius,
                                                 const Vector3& pos,
                                                 const Vector3& dir)
    : kinematics(radius, pos, dir), leftWheelVel(0.0), rightWheelVel(0.0) {}

void DifferentialDriveMotion::SetWheelVelocities(double left, double right) {
  leftWheelVel = left;
  rightWheelVel = right;
}

void DifferentialDriveMotion::Update(double dt, Vector3& pos, Vector3& dir,
                                     Vector3& vel, double arenaWidth,
                                     double arenaHeight) {
  Vector3 posBefore = pos;

  kinematics.Update(dt, leftWheelVel, rightWheelVel, pos, vel);

  // Wall collision: revert position and reflect velocity so we stay in bounds
  if (pos[0] > arenaWidth - vel.Length() ||
      pos[1] > arenaHeight - vel.Length() || pos[0] < vel.Length() ||
      pos[1] < vel.Length()) {
    pos = posBefore;
    vel = vel * -1.0;
    kinematics.SetPosition(pos);
  }

  if (vel.Length() > 0) {
    dir = vel.Normalized();
  }
  kinematics.SetDirection(dir);
}