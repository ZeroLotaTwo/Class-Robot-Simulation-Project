#ifndef team_001_8_project_include_sim_sensors_GenericSensor_H_
#define team_001_8_project_include_sim_sensors_GenericSensor_H_

#include <iostream>

#include "sim/entities/BraitenbergVehicle.h"
#include "sim/entities/EnergyEntity.h"
#include "sim/entities/Light.h"
#include "sim/entities/Predator.h"
#include "sim/entities/Robot.h"
#include "sim/entities/Water.h"
#include "sim/sensors/Sensor.h"

/**
 * @brief This is a sensor that is used to sense the locations/data of
 *        all of the currently supported entities
 */
class GenericSensor : public Sensor {
 public:
  /**
   * @brief Constructor for the GenericSensor
   * @param entityTarget The entity the sensor will detect.
   * @param entityId     The Id of the entity not to target.
   *                     This is so the movement will sense itself.
   * @param arena        The simulation model to iterate though the entities.
   * @param pos          Current position of the entity to be changed.
   * @param dir          Current direction of the entity to be changed.
   * @param radiusAway   How far away the sensor will read from the vehicle.
   * @param angle        Angle used to move the sensor on a cirlce around the
   *                     the Entity.
   */
  GenericSensor(std::string entityTarget, int entityId,
                const ISimulationModel& arena, Vector3 pos, Vector3 dir,
                double radiusAway, double angle);
  ~GenericSensor();
  /**
   * @brief Used to update the position the sensor will be
   *        with respect to it 'attached' entity.
   * @param entityNewPos The entity the sensor will detect.
   * @param entityNewDir The Id of the entity not to target.
   */
  virtual void Update(Vector3 entityNewPos, Vector3 entityNewDir);
  /**
   * @brief Interface to retrive the sensor's value.
   * @return returns the double value of the sensor.
   */
  double GetSensorValue();
  /**
   * @brief Interface to retrive the how far away the closest entity is.
   *        with [0,infinity) representing that it has found an entity.
   *        And (-infinity, 0) representing that it has not found an entity.
   *        This implementation returns -1.
   * @return returns the distance to the closest entity
   *         with -1 meaning no entity was found.
   */
  double GetDist();
  /**
   * @brief Interface to retrive the closest entity.
   * @return returns the closest entity
   *         with nullptr meaning no entity was found.
   */
  EntityBase* GetClosestGeneric();

 private:
  // String representation of what entity the sensor looks for.
  std::string entityTarget;
  // the id of the entity to ignore. Usually the entity this is attached to.
  int entityId = -1;
  /**
   * @brief Interface to retrive the closest entity.
   *        (Note) this is a templated helper function for the public one above.
   * @return returns the closest entity
   *         with nullptr meaning no entity was found.
   */
  template <typename EntityType>
  EntityType* GetClosestGeneric() {
    auto entities = &arena.GetEntities();
    if (entities->size() < 1) return nullptr;
    double minDistance = -1;
    EntityType* closest = nullptr;
    for (auto entity : *entities) {
      EntityType* cur = dynamic_cast<EntityType*>(entity);
      if (cur == nullptr || cur->GetId() == entityId) continue;
      Vector3 ePos = Vector3(cur->GetPosition());
      double curDist = (ePos - this->pos).Length();
      if (curDist < minDistance || minDistance == -1) {
        minDistance = curDist;
        closest = cur;
      }
    }
    return closest;
  }

  /**
   * @brief Interface to retrive the how far away the closest entity is.
   *        with [0,infinity) representing that it has found an entity.
   *        And (-infinity, 0) representing that it has not found an entity.
   *        This implementation returns -1.
   *        (Note) this is a templated helper function for the public one above.
   * @return returns the distance to the closest entity
   *         with -1 meaning no entity was found.
   */
  template <typename EntityType>
  double GetGenericDist() {
    auto entities = &arena.GetEntities();
    double minDistance = -1;
    for (auto entity : *entities) {
      EntityType* cur = dynamic_cast<EntityType*>(entity);
      if (cur == nullptr || cur->GetId() == entityId) continue;
      Vector3 ePos = Vector3(cur->GetPosition());
      //   std::cout << "SENSOR POS: " << this->pos[0] << ", " << this->pos[1]
      //   << std::endl; std::cout << "ENTITY POS: " << ePos[0] << ", " <<
      //   ePos[1] << std::endl;
      double curDist = (ePos - this->pos).Length();
      //   std::cout << "CUR DIST: " << curDist << std::endl;
      if (curDist < minDistance || minDistance == -1) {
        minDistance = curDist;
      }
    }
    // std::cout << minDistance << std::endl;
    return minDistance;
  }
};

#endif