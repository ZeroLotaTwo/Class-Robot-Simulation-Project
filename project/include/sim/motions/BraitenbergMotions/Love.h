#ifndef team_001_8_project_include_sim_motion_BraitenbergMotions_Love_H_
#define team_001_8_project_include_sim_motion_BraitenbergMotions_Love_H_

#include "json.hpp"
#include "sim/motions/Interfaces/IndividualMotionI.h"
#include "sim/physics/DifferentialDriveKinematics.h"
/**
 * @brief This is a motion that inherits from the IndividualMotion Interface.
 *        This is a raw motion and is used in other files.
 *        For example BraitenbergMotion.h and CompositeMotion.h
 */
class Love : public IndividualMotionI {
 public:
  /**
   * @brief Constructor for the Love motion.
   * @param arenaWidth  The width of the simulation model/arena.
   * @param arenaHeight The height of the simulation model/arena.
   * @param data        Json that contains metadata about the entity.
   */
  Love(double arenaWidth, double arenaHeight, const nlohmann::json& data);

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
  // Radius of the entity.
  double radius;
  // Width of arena.
  double arenaWidth;
  // Height of arena.
  double arenaHeight;
  // Maximum speed of the entity.
  double maxSpeed;
  // Current speed scalar of the entity.
  double speed = 0;
  // Sub motion used the the BV motions.
  // And it can control both wheels independantly.
  DifferentialDriveKinematics kinematics;
};

#endif