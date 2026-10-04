/**
 * @file PredToEntity.h
 *
 * @brief Template adapter that wraps a Predator and exposes it as a concrete
 *        IEntity subtype (e.g., Light, EnergyEntity) while delegating Update().
 */

#ifndef team_001_8_project_include_sim_adapters_PredToEntity_H_
#define team_001_8_project_include_sim_adapters_PredToEntity_H_

#include <utility>

#include "sim/entities/BraitenbergVehicle.h"
#include "sim/entities/EnergyEntity.h"
#include "sim/entities/Light.h"
#include "sim/entities/Predator.h"
#include "sim/entities/Robot.h"
#include "sim/entities/Water.h"

template <typename Base>
/**
 * @brief Constructor that is a facade that is mostly for the sensors
 *        but is also for it's disguise.
 * @param predator  Heap-allocated Predator which will be the base entity
 * @param args      Variable length args to do the bareminimum needed
 *                  for the inherited class.
 */
class PredatorAdapter : public Base {
 public:
  template <typename... Args>
  PredatorAdapter(Predator* predator, Args&&... args)
      : Base(std::forward<Args>(args)...), predator(predator) {
    SetFakeType();
  }
  /**
   * @brief Helper function to help with disgusing the predator
   *        This will set the predator to it's falseType initialized
   *        in the predator class.
   */
  void SetFakeType() {
    std::string typeName = predator->falseType;
    if (predator->motionSwaped) {
      typeName = "predator";
    }
    if (typeName == "energy") {
      Base::template SetType<EnergyEntity>(typeName);
    } else if (typeName == "light") {
      Base::template SetType<Light>(typeName);
    } else if (typeName == "bv") {
      Base::template SetType<BraitenbergVehicle>(typeName);
    } else if (typeName == "robot") {
      Base::template SetType<Robot>(typeName);
    } else if (typeName == "water") {
      Base::template SetType<Water>(typeName);
    } else {
      Base::template SetType<Predator>(typeName);
    }
  }

  virtual ~PredatorAdapter() override {
    // Adapter and underlying Predator share the same Motion*; EntityBase
    // deletes movement. Clear our pointer so only Predator::~EntityBase frees
    // it once.
    this->movement = nullptr;
    delete predator;
  }

  /**
   * @brief This update moves two entities with the adaptor being the cover
   *        and uses the underlying predator to move around.
   */
  virtual void Update(double dt) override {
    predator->Update(dt);
    SetFakeType();
    // Base::Update(dt);
    this->pos = predator->GetPos();
    this->vel = predator->GetVel();
    this->dir = predator->GetDir();
  }

 private:
  // Underlying predator entity that is already initialized.
  Predator* predator = nullptr;
};

#endif  // PRED_TO_ENTITY_H_