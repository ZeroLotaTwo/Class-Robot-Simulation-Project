/**
 * @file BraitenbergMotion.h
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#ifndef team_001_8_project_include_sim_motion_BraitenbergMotion_H_
#define team_001_8_project_include_sim_motion_BraitenbergMotion_H_

#include "sim/motions/BraitenbergMotions/Aggression.h"
#include "sim/motions/BraitenbergMotions/Explore.h"
#include "sim/motions/BraitenbergMotions/Fear.h"
#include "sim/motions/BraitenbergMotions/Love.h"
#include "sim/motions/Interfaces/IndividualMotionI.h"
#include "sim/motions/Motion.h"
#include "sim/sensors/GenericSensor.h"

/**
 * @brief Composite motion for Braitenberg-style vehicles.
 *
 * Selects one of fear, explore, love, or aggression behaviours and wires it
 * to left/right GenericSensor instances. Update() runs sensor sampling then
 * delegates to the behaviour.
 */
class BraitenbergMotion : public Motion {
 public:
  /**
   * @brief Constructor for the BraitenbergMotion.
   * @param motionType  String representing the motion to be used.
   * @param arenaWidth  The width of the simulation model/arena.
   * @param arenaHeight The height of the simulation model/arena.
   * @param data        Json that contains metadata about the entity.
   * @param leftSensor  Heap-allocated sensor that is initialized
   *                    in simulation model
   * @param rightSensor Heap-allocated sensor that is initialized
   *                    in simulation model
   */
  BraitenbergMotion(std::string motionType, double arenaWidth,
                    double arenaHeight, const nlohmann::json& data,
                    GenericSensor* leftSensor, GenericSensor* rightSensor);

  virtual ~BraitenbergMotion() override;

  /**
   * @brief This will move an entity given the arguments
   *        with the descriped motion.
   * @param dt   The delta time is the change in time between each call.
   * @param pos  Current position of the entity to be changed.
   * @param vel  Current velocity of the entity to be changed.
   * @param dir  Current direction of the entity to be changed.
   */
  void Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir) override;

 private:
  // the motion that the constructor will initialize.
  IndividualMotionI* motion = nullptr;
  // Left sensor given by the simulation model.
  GenericSensor* leftSensor = nullptr;
  // Right sensor given by the simulation model.
  GenericSensor* rightSensor = nullptr;
};

#endif
