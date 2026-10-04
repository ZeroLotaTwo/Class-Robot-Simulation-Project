#ifndef team_001_8_project_include_sim_motion_BounceMotion_H_
#define team_001_8_project_include_sim_motion_BounceMotion_H_

#include "sim/motions/Interfaces/IndividualMotionI.h"

class BounceMotion : public IndividualMotionI {
 public:
  /**
   * @brief Constructor for the Bounce motion.
   * @param arenaWidth  The width of the simulation model/arena.
   * @param arenaHeight The height of the simulation model/arena.
   * @param data        Json that contains metadata about the entity.
   */
  BounceMotion(double arenaWidth, double arenaHeight,
               const nlohmann::json& data);

  /**
   * @brief This will move an entity given the arguments
   *        with the descriped motion.
   * @param dt   The delta time is the change in time between each call.
   * @param pos  Current position of the entity to be changed.
   * @param vel  Current velocity of the entity to be changed.
   * @param dir  Current direction of the entity to be changed.
   */
  virtual void Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir);

 private:
  // Scalar speed for movement.
  double speed;
  // Radius of the entity for wall collisioins.
  double radius;
  // Width of arena.
  double arenaWidth;
  // Height of arena.
  double arenaHeight;
};

#endif