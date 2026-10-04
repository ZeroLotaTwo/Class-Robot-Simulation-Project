/**
 * @file DifferentialDriveMotion.h
 */

#ifndef team_001_8_project_include_sim_entities_DifferentialDriveMotion_H_
#define team_001_8_project_include_sim_entities_DifferentialDriveMotion_H_

#include "sim/Vector3.h"
#include "sim/physics/DifferentialDriveKinematics.h"

/**
 * @brief Adapter that turns DifferentialDriveKinematics into a motion
 */
class DifferentialDriveMotion {
 public:
  /**
   * @brief Construct a differential drive motion
   *
   * @param radius Radius of the entity
   * @param pos Position of the entitiy
   * @param dir Direction of the entity
   *
   */
  DifferentialDriveMotion(double radius, const Vector3& pos,
                          const Vector3& dir);

  /**
   * @brief Set the current left and right wheel velocities
   *
   * @param left Left wheel velocity.
   * @param right Right wheel velocity.
   */
  void SetWheelVelocities(double left, double right);

  /**
   * @brief Update the entity pose using the differential drive model.
   *
   * @param dt Time step since last update
   * @param pos Entity position (in/out)
   * @param dir Entity direction (in/out)
   * @param vel Entity velocity (in/out)
   * @param arenaWidth Width of the arena
   * @param arenaHeight Height of the arena
   */
  void Update(double dt, Vector3& pos, Vector3& dir, Vector3& vel,
              double arenaWidth, double arenaHeight);

 private:
  DifferentialDriveKinematics kinematics;
  double leftWheelVel;
  double rightWheelVel;
};

#endif