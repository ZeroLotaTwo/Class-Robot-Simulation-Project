/**
 * @file ConvertPred.h
 *
 * Converts a raw Predator* + JSON description into the correct IEntity*
 * subtype so that it renders and behaves as the right visual entity while
 * still running Predator logic each tick.
 */

#ifndef team_001_8_project_include_sim_adapters_ConvertPred_H_
#define team_001_8_project_include_sim_adapters_ConvertPred_H_

#include "sim/adapters/PredToEntity.h"
#include "sim/entities/BraitenbergVehicle.h"
#include "sim/entities/EnergyEntity.h"
#include "sim/entities/Light.h"
#include "sim/entities/Predator.h"
#include "sim/entities/Robot.h"
#include "sim/entities/Water.h"

/**
 * @brief Converts a Predator + JSON data into the appropriate IEntity subtype.
 *
 * The JSON "type" field decides which Base class the adapter inherits from,
 * so the frontend renderer sees the right visual while the Predator's Update
 * runs the actual behaviour.
 *
 * Ownership of the Predator* is transferred to the returned PredatorAdapter.
 * The caller owns the returned IEntity*.
 */
class ConvertPred {
 public:
  /**
   * @brief Constructor.
   * @param predator  Heap-allocated Predator whose ownership will be
   *                  transferred to the returned adapter.
   * @param data      JSON description of the entity (same format used by
   *                  SimulationModel::CreateEntity).
   */
  ConvertPred(Predator* predator, const json& data)
      : predator(predator), data(data) {}

  /**
   * @brief Builds and returns the adapter entity.
   *
   * The returned pointer is heap-allocated; the caller is responsible for
   * its lifetime (or it can be handed straight to SimulationModel::AddEntity).
   *
   * @return An EntityBase* whose Update() runs Predator logic, or nullptr if
   * the "type" field is unrecognised.
   */
  EntityBase* ConvertToEntity();

 private:
  Predator* predator;  ///< Non-owning until ConvertToEntity() transfers it.
  const json data;     ///< Copied by value to avoid dangling-reference UB.
};

#endif  // CONVERT_PRED_H_