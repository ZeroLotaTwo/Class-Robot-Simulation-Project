#include "sim/entities/EnergyEntity.h"

EnergyEntity::EnergyEntity(Motion* movement, Vector3 pos, Vector3 dir,
                           double radius, const json& data)
    : Light(movement, pos, dir, radius, data) {
  SetType<EnergyEntity>("EnergyEntity");
}

EnergyEntity::~EnergyEntity() = default;

double EnergyEntity::GetChargeFromOverlapTime(double time) const {
  return time * GetIntensity() / 5.0;
}

bool EnergyEntity::CanIdentifyAsEnergy(double distance) const {
  return distance <= 5.0 * radius;
}
