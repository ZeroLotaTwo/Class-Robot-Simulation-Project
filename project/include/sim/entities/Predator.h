#ifndef team_001_8_project_include_sim_entities_Predator_H_
#define team_001_8_project_include_sim_entities_Predator_H_

#include "sim/entities/Robot.h"
class GenericSensor;  // Forawrd declaring for the generic sensor
#include "sim/entities/Light.h"

/**
 * @brief Predator robot that can drain energy from the closest Robot.
 *
 * Predators are Robots for energy rules, but expose a separate update(dt)
 * used by PredatorAdapter so they can be wrapped as other visual entities.
 */
class Predator : public Robot {
 public:
  /**
   * @brief Constructor for the Predator Entity.
   * @param movement   Heap-allocated movement initialized in simulation model
   *                   that describes its default motion.
   * @param attack     Heap-allocated movement that is initialized in
   *                   simulation model that descripes its
   *                   motion when it attacks.
   * @param sensor     Heap-allocated sensor that is initialized
   *                   in simulation model to detect robots to eat.
   * @param pos        Initial postion that the Predator will have.
   * @param dir        Initial direction that the Predator will have.
   * @param radius     Controls how large the Predator will be.
   * @param data       Json that contains metadata about the entity.
   */
  Predator(Motion* movement, Motion* attack, GenericSensor* sensor, Vector3 pos,
           Vector3 dir, double radius, const json& data);
  virtual ~Predator() override;
  /**
   * @brief Updates the position of the entity in the simulation.
   * @param dt The delta time is the change in time between each call.
   */
  virtual void Update(double dt) override;

  /**
   * @brief Used to get the current position of the pred entity.
   * @return Returns a 3 dimensional vector that (x,y,z).
   */
  Vector3 GetPos();
  /**
   * @brief Used to get the current direction of the pred entity.
   * @return Returns a 3 dimensional vector that (x,y,z).
   */
  Vector3 GetDir();
  /**
   * @brief Used to get the current velocity of the pred entity.
   * @return Returns a 3 dimensional vector that (x,y,z).
   */
  Vector3 GetVel();
  /**
   * @brief Helper method to help with disgusing the predator
   *        This will set the predator to it's falseType.
   */
  void SetFalseType();
  // String that descripes the type of the predator's disguise.
  std::string falseType;
  // Used to tell if the predator is using the attack motion.
  // False means it is not attacking.
  bool motionSwaped = false;
  // Method variable that holds the predator's attack motion.
  Motion* attack;
  // This is the predator's robot sensor.
  GenericSensor* sensor;

 private:
  /**
   * @brief Helper method to determine if the predator is close enough
   *        to drain target entity battery.
   * @return Returns a boolean with True meaning it can drain the battery.
   */
  bool CanDrainEnergy();
  /**
   * @brief Helper method to drain the intersecting robot.
   */
  void DrainClosestRobotEnergy();
};

#endif