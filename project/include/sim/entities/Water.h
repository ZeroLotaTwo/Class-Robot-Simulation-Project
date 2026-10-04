#ifndef team_001_8_project_include_sim_entities_Water_H_
#define team_001_8_project_include_sim_entities_Water_H_

#include "json.hpp"
#include "sim/entities/EntityBase.h"
#include "sim/motions/SimpleMotion.h"

using json = nlohmann::json;

/**
 * @brief Water entities drain robot charge on intersection.
 */
class Water : public EntityBase {
 public:
  /**
   * @brief Constructor for the Watter entity.
   * @param movement   Heap-allocated movement initialized in simulation model
   *                   that describes its default motion.
   *                   motion when it attacks.
   * @param pos        Initial postion that the Water will have.
   * @param dir        Initial direction that the Water will have.
   * @param radius     Controls how large the Water will be.
   * @param data       Json that contains metadata about the entity.
   */
  Water(Motion* movement, Vector3 pos, Vector3 dir, double radius,
        const json& data);
  /**
   * @brief Updates the position of the entity in the simulation.
   * @param dt The delta time is the change in time between each call.
   */
  void Update(double dt) override;

  virtual ~Water() override;

 protected:
  // Descripes the current velocity of the water.
  Vector3 vel;
};

#endif