/**
 * @file Motion.h
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#ifndef team_001_8_project_include_sim_motion_Motion_H_
#define team_001_8_project_include_sim_motion_Motion_H_

#include <string>

#include "json.hpp"
#include "sim/Vector3.h"

/**
 * @brief Abstract base for all motion strategies.
 *
 * Subclasses implement Update() to change position, velocity, and direction
 * each timestep. Entities hold a Motion* and delegate movement to it.
 */
class Motion {
 public:
  /**
   * @brief Constructs a motion with a string label (often the JSON "type").
   */
  explicit Motion(std::string motionType) : motionType(motionType) {}

  virtual ~Motion() = default;

  /**
   * @brief Advances motion for one timestep.
   * @param dt   Time delta since last update.
   * @param pos  Entity position (read/write).
   * @param vel  Entity velocity (read/write).
   * @param dir  Entity facing direction (read/write).
   */
  virtual void Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir) {
    return;
  }

 protected:
  // String representation of the motion type.
  std::string motionType;
};

#endif
