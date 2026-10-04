#include "sim/adapters/ConvertPred.h"

EntityBase* ConvertPred::ConvertToEntity() {
  if (!data.contains("position") || !data.contains("direction") ||
      !data.contains("radius")) {
    return nullptr;
  }

  Vector3 pos(data["position"][0], data["position"][1], data["position"][2]);
  Vector3 dir =
      Vector3(data["direction"][0], data["direction"][1], data["direction"][2])
          .Normalized();
  double radius = data["radius"].get<double>();
  const std::string type = predator->falseType;
  double arenaWidth = data.value("arenaWidth", 0.0);
  double arenaHeight = data.value("arenaHeight", 0.0);

  Motion* movement = predator->movement;
  if (type == "light") {
    // Predator wearing a Light skin — no battery fields needed.
    return new PredatorAdapter<Light>(predator, movement, pos, dir, radius,
                                      data);
  }
  if (type == "robot") {
    return new PredatorAdapter<Robot>(predator, movement, pos, dir, radius,
                                      data);
  }
  // NOTE: Predator disguise as a BraitenbergVehicle requires constructing
  // a BraitenbergVehicle with real LightSensor unique_ptrs. That wiring is
  // not yet implemented, so we skip this disguise for now.
  // if(type == "bv"){
  //     // Fine to have this NULL b/c only update on the BV uses the sensors
  //     return new PredatorAdapter<BraitenbergVehicle>(predator, NULL, NULL,
  //                 pos, dir, radius, arenaWidth, arenaHeight, motion);
  // }
  if (type == "energy") {
    return new PredatorAdapter<EnergyEntity>(predator, movement, pos, dir,
                                             radius, data);
  }
  if (type == "water") {
    return new PredatorAdapter<Water>(predator, movement, pos, dir, radius,
                                      data);
  }
  // Disguise as a plain Predator is equivalent to just using the Predator
  // directly as a Robot in the scene; the adapter adds no value here, so
  // we omit this case for now.
  // if(type == "predator"){
  //     return new PredatorAdapter<Predator>(predator, movement, nullptr,
  //     nullptr,
  //       pos, dir, radius, arenaWidth, arenaHeight, data);
  // }
  if (type == "bv") {
    return new PredatorAdapter<BraitenbergVehicle>(
        predator, movement, nullptr, nullptr, pos, dir, radius, data);
  }
  return new PredatorAdapter<Predator>(predator, movement, nullptr, nullptr,
                                       pos, dir, radius, data);
}