#ifndef team_001_8_project_include_sim_motion_SimpleMotions_DefaultMotion_H_
#define team_001_8_project_include_sim_motion_SimpleMotions_DefaultMotion_H_

#include "sim/motions/Interfaces/IndividualMotionI.h"

class DefaultMotion : public IndividualMotionI {
 public:
  /**
   * @brief Constructor for the Default motion that does not move.
   */
  DefaultMotion() {}

  /**
   * @brief This will move an entity given the arguments
   *        with the descriped motion.
   * @param dt   The delta time is the change in time between each call.
   * @param pos  Current position of the entity to be changed.
   * @param vel  Current velocity of the entity to be changed.
   * @param dir  Current direction of the entity to be changed.
   */
  virtual void Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir) {
    return;
  }
};

#endif