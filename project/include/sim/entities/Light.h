/**
 * @file Light.h
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#ifndef team_001_8_project_include_sim_entities_Light_H_
#define team_001_8_project_include_sim_entities_Light_H_

#include "json.hpp"
#include "sim/entities/EntityBase.h"
#include "sim/motions/SimpleMotion.h"
using json = nlohmann::json;

/**
 * @brief Class representing lights in the simulation; inherits EntityBase.
 */
class Light : public EntityBase {
 public:
  /**
   * @brief consturctor for the Light entity.
   *
   * @param pos - starting position for light in Vector3 form
   * @param dir - starting direction for light in Vector3 form
   * @param radius - radius of the light for its size
   * @param motion - motion specification for the light in json form
   */
  Light(Motion* movement, Vector3 pos, Vector3 dir, double radius,
        const json& data);

  /**
   * @brief destructor for light
   */
  virtual ~Light() override;

  /**
   * @brief update method for light, which moves the light entitiy according
   * to its motion type
   *
   * @param dt - how much time passed since last update
   */
  void Update(double dt);
  /**
   * @brief Method to retrieve the intensity of the light.
   *
   * @return Gives back a double that represents how bright the light is.
   */
  double GetIntensity() const;

 protected:
  // velocity vector
  Vector3 vel;
};

#endif
