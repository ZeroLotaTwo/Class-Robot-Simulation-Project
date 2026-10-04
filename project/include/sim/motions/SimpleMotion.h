/**
 * @file SimpleMotion.h
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#ifndef team_001_8_project_include_sim_motion_SimpleMotion_H_
#define team_001_8_project_include_sim_motion_SimpleMotion_H_

#include "sim/motions/Interfaces/IndividualMotionI.h"
#include "sim/motions/Motion.h"
#include "sim/motions/SimpleMotions/Around.h"
#include "sim/motions/SimpleMotions/BackAndForth.h"
#include "sim/motions/SimpleMotions/BounceMotion.h"
#include "sim/motions/SimpleMotions/DefaultMotion.h"
#include "sim/motions/SimpleMotions/KeyboardMotion.h"

class Vector3;

/**
 * @brief Composite motion for non-Braitenberg entities.
 *
 * Picks a concrete @ref IndividualMotionI implementation from the JSON
 * `motion.type` field (default, bounce, keyboard, around, back_and_forth)
 * and delegates each Update() to that object.
 */
class SimpleMotion : public Motion {
 public:
  /**
   * @brief Constructor for the BraitenbergMotion.
   * @param motionType  String representing the motion to be used.
   * @param arenaWidth  The width of the simulation model/arena.
   * @param arenaHeight The height of the simulation model/arena.
   * @param data        Json that contains metadata about the entity.
   */
  SimpleMotion(std::string motionType, double arenaWidth, double arenaHeight,
               const nlohmann::json& data);

  virtual ~SimpleMotion() override;

  /**
   * @brief This will move an entity given the arguments
   *        with the descriped motion.
   * @param dt   The delta time is the change in time between each call.
   * @param pos  Current position of the entity to be changed.
   * @param vel  Current velocity of the entity to be changed.
   * @param dir  Current direction of the entity to be changed.
   */
  void Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir) override;

  /**
   * @brief  This is used to the underlying motion.
   * @return Returns the underlying member variable motion.
   */
  IndividualMotionI* GetMotion() const;

 private:
  IndividualMotionI* motion = nullptr;
};

#endif
