#ifndef team_001_8_project_include_sim_sensors_Sensor_H_
#define team_001_8_project_include_sim_sensors_Sensor_H_

#include <math.h>

#include "core/ISimulationModel.h"
#include "sim/Vector3.h"

/**
 * @brief This is the sensor interface that GenericSensor uses.
 *        (Note) there used to be more sensors but GenericSensor
 *        handles all of the entities.
 */
class Sensor {
 public:
  /**
   * @brief Constructor for the Sensor interface that can be instantiated
   * @param arena        The simulation model to iterate through the entities.
   * @param pos          Current position of the entity to be changed.
   * @param dir          Current direction of the entity to be changed.
   * @param radiusAway   How far away the sensor will read from the vehicle.
   * @param angle        Angle used to move the sensor on a cirlce around
   *                     the Entity. Uses the +X axis for start.
   *                     Like with how polar cordinates work.
   */
  Sensor(const ISimulationModel &arena, Vector3 pos, Vector3 dir,
         double radiusAway, double angle)
      : arena(arena),
        pos(pos),
        dir(dir),
        radiusAway(radiusAway),
        angle(angle * M_PI / 180) {}
  virtual ~Sensor() {}
  /**
   * @brief Used to update the position the sensor will be
   *        with respect to it 'attached' entity.
   * @param entityNewPos The entity the sensor will detect.
   * @param entityNewDir The Id of the entity not to target.
   */
  virtual void Update(Vector3 entitynewPos, Vector3 entityNewDir) = 0;

 protected:
  // Postion of the sensor;
  Vector3 pos;
  // Directoin of the sensor;
  Vector3 dir;
  // The simulation model to iterate through the entities.
  const ISimulationModel &arena;
  // How far away the sensor will read from the vehicle.
  double radiusAway;
  // Angle used to move the sensor on a cirlce around the Entity.
  double angle;

  /*
  Calculates where the sensor is and passes it inside the variable
  that is given as an argument.
  */
  virtual void CalcSensorPos(Vector3 &newPos, Vector3 &newDir) {
    // For expected behavior, newDir should already be normalized.
    pos[0] = (newDir[0] * cos(this->angle) - newDir[1] * sin(this->angle)) *
                 radiusAway +
             (newPos)[0];
    pos[1] = (newDir[0] * sin(this->angle) + newDir[1] * cos(this->angle)) *
                 radiusAway +
             (newPos)[1];
    pos[2] = (newPos)[2];
  }
};

#endif