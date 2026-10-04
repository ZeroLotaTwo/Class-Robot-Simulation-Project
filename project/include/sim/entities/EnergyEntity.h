#ifndef team_001_8_project_include_sim_entities_EnergyEntity_H_
#define team_001_8_project_include_sim_entities_EnergyEntity_H_

#include "sim/entities/Light.h"

/**
 * @brief Energy stations emit like lights (EM); robots recharge on overlap.
 */
class EnergyEntity : public Light {
 public:
  /**
   * @brief Constructor for the EnergyEntity.
   * @param movement    Heap-allocated movement initialized in simulation mode
   * @param pos         Initial postion that the EnergyEntity will have.
   * @param dir         Initial direction that the EnergyEntity will have.
   * @param radius      Controls how large the EnergyEntity will be.
   * @param data        Json that contains metadata about the entity.
   */
  EnergyEntity(Motion* movement, Vector3 pos, Vector3 dir, double radius,
               const json& data);
  virtual ~EnergyEntity() override;

  /**
   * @brief Total charge gained after `time` seconds at overlap recharge rate

   */
  double GetChargeFromOverlapTime(double time) const;

  /**
   * @brief True when distance from sensor to this source is within 5*radius —
   *        only then can a sensor tell this source is energy vs a plain light.
   */
  bool CanIdentifyAsEnergy(double distance) const;
};

#endif
