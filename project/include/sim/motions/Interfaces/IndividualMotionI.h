/**
 * @file IndividualMotionI.h
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#ifndef team_001_8_project_include_sim_motion_IndividualMotionI_H_
#define team_001_8_project_include_sim_motion_IndividualMotionI_H_

#include <string>

#include "json.hpp"
#include "sim/Vector3.h"

/**
 * @brief Interface for concrete motion algorithms used inside composite
 * motion classes.
 *
 * SimpleMotion and BraitenbergMotion own an IndividualMotionI* and forward
 * Update() to it. Braitenberg behaviours also receive sensor readings via
 * SetSensorValues().
 */
class IndividualMotionI {
 public:
  virtual ~IndividualMotionI() = default;

  /**
   * @brief This will move an entity given the arguments
   *        with the descriped motion.
   * @param dt   The delta time is the change in time between each call.
   * @param pos  Current position of the entity to be changed.
   * @param vel  Current velocity of the entity to be changed.
   * @param dir  Current direction of the entity to be changed.
   */
  virtual void Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir) = 0;

  // Below here is more for the BraitenbergMotions

  /**
   * @brief Injects left/right sensor readings for Braitenberg-style motions.
   */
  virtual void SetSensorValues(double leftVal, double rightVal) {
    this->leftVal = leftVal;
    this->rightVal = rightVal;
  }

 protected:
  // Sensor values to be used by the BraitenbergMotions
  double leftVal = 0;
  double rightVal = 0;
};

#endif
