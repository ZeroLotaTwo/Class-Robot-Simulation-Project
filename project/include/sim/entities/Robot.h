/**
 * @file Robot.h
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#ifndef team_001_8_project_include_sim_entities_Robot_H_
#define team_001_8_project_include_sim_entities_Robot_H_

#include <set>
#include <string>

#include "sim/entities/EntityBase.h"
#include "sim/motions/SimpleMotion.h"

/**
 * @brief Defines a robot that can move around in an arena.
 */

class Robot : public EntityBase {
 public:
  /**
   * @brief Initialize a robot with a motion behavior.
   */

  Robot(Motion* movement, Vector3 pos, Vector3 dir, double radius,
        const json& data);

  /**
   * @brief Destructor for robot.
   */
  virtual ~Robot() {}

  /**
   * @brief Update a robot over time.
   * @param dt A time delta since the last call to Update.
   */
  void Update(double dt) override;

  /** Current energy (charge). */
  double GetCharge() const { return charge; }
  /** Maximum energy capacity made at creation. */
  double GetMaxCharge() const { return maxCharge; }
  /** Adds energy (e.g. when intersecting an energy source), clamped to
   * maxCharge. */
  void AddCharge(double amount);
  /** Explicit drain helper if other systems need it. */
  void DrainCharge(double amount);

 protected:
  /**
   * @brief Applies iteration-2 energy drain from movement and timestep.
   * Subclasses that override Update should call this after updating position.
   * @param dt Timestep.
   * @param oldPos Position before integration.
   * @param newPos Position after integration.
   */
  void DrainEnergyForMovement(double dt, const Vector3& oldPos,
                              const Vector3& newPos);

  Vector3 vel;

  /** Energy capacity and current charge (robots must recharge at energy
   * entities). */
  double charge;
  double maxCharge;
};

#endif