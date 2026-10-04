/**
 * @file BriatenbergVehicle.h
 *
 * @brief This is a entity that is a Robot, but also has sensors.
 */

#ifndef team_001_8_project_include_sim_entities_BraitenbergVehicle_H_
#define team_001_8_project_include_sim_entities_BraitenbergVehicle_H_

class GenericSensor;  // Forawrd declaring for the generic sensor
#include "sim/entities/Robot.h"
#include "sim/motions/BraitenbergMotion.h"

class BraitenbergVehicle : public Robot {
 public:
  /**
   * @brief Constructor for the BraitenbergVehicle
   * @param movement    Heap-allocated movement initialized in simulation model
   * @param leftSensor  Heap-allocated sensor that is initialized
   *                    in simulation model
   * @param rightSensor Heap-allocated sensor that is initialized
   *                    in simulation model
   * @param pos         Initial postion that the BraitenbergVehicle will have.
   * @param dir         Initial direction that the BraitenbergVehicle will have.
   * @param radius      Controls how large the BraitenbergVehicle will be.
   * @param data        Json that contains metadata about the entity.
   */
  BraitenbergVehicle(Motion* movement, GenericSensor* leftSensor,
                     GenericSensor* rightSesor, Vector3 pos, Vector3 dir,
                     double radius, const json& data);

  virtual ~BraitenbergVehicle();
  /**
   * @brief Updates the position of the entity in the simulation.
   * @param dt The delta time is the change in time between each call.
   */
  virtual void Update(double dt) override;
  /**
   * @brief Method to read off a sensor value.
   * @return Gives back a double value given by the genericSensor object.
   */
  double GetLeftLightSensorValue();
  /**
   * @brief Method to read off a sensor value.
   * @return Gives back a double value given by the genericSensor object.
   */
  double GetRightLightSensorValue();
  // Initialized in simulation model
  GenericSensor* leftSensor = nullptr;
  // Initialized in simulation model
  GenericSensor* rightSensor = nullptr;

 private:
  // The maximum speed the robot is allowed to go.
  double maxSpeed;
};

#endif
