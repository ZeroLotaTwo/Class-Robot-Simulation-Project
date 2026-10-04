/**
 * @file SimulationModel.h
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include <cmath>
#include <memory>

#include "core/ISimulationModel.h"
#include "sim/adapters/ConvertPred.h"
#include "sim/adapters/PredToEntity.h"
#include "sim/entities/BraitenbergVehicle.h"
#include "sim/entities/EnergyEntity.h"
#include "sim/entities/Light.h"
#include "sim/entities/Predator.h"
#include "sim/entities/Robot.h"
#include "sim/entities/Water.h"
#include "sim/motions/BraitenbergMotion.h"
#include "sim/motions/Interfaces/IndividualMotionI.h"
#include "sim/motions/SimpleMotion.h"
#include "sim/sensors/GenericSensor.h"

/**
 * @brief Concrete simulation model that manages entities, lights, and scene
 * updates.
 */
class SimulationModel : public ISimulationModel {
 public:
  /**
   * @brief Simulation model constructor.
   */
  SimulationModel();

  /**
   * @brief Virtual destructor is needed for dynamic memory management in
   * inherited classes.
   */
  virtual ~SimulationModel();

  /**
   * @brief Creates a scene for a simulation (e.g. sets boundaries and initial
   * entities).
   * @param data Data structure that stores scene data using json library.
   * @return Modifications to the scene based on the simulation.
   */
  virtual json CreateScene(const json& data);

  /**
   * @brief Updates a simulation by incrementing the time.
   * @param dt A time delta from the last time Update was called.
   */
  virtual void Update(double dt);

  /**
   * @brief Creates an entity based on json data structure.
   * @param data Data structure for an entity.
   * @return Pointer to the created entity, or nullptr on failure.
   */
  virtual IEntity* CreateEntity(const json& data) const;

  /**
   * @brief Adds an entity to the simulation model.
   * @param entity An entity object.
   */
  virtual void AddEntity(IEntity* entity);

  /**
   * @brief Handles input events (e.g. keyboard or mouse input).  Events can
   * also be generic external input.
   * @param event The event name.
   * @param data Additional event data.
   */
  virtual void HandleEvent(const std::string& event, const json& data);

  /**
   * @brief Gets all the entities in the simulation.
   * @return A vector of entities.
   */
  const std::vector<IEntity*>& GetEntities() const { return entities; }

  void ApplyRobotWaterDrain(double dt);

 private:
  int width;
  int height;
  std::vector<IEntity*> entities;
};

#endif
