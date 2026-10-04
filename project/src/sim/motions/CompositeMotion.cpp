// #include "sim/motions/CompositeMotion.h"

// #include <iostream>

// CompositeMotion::CompositeMotion(const ISimulationModel& arena, std::string
// motionType, int entityId, double arenaWidth, double arenaHeight, const
// nlohmann::json& data) : Motion(motionType){
//     nlohmann::json motionJson = data.value("motion",
//     nlohmann::json::object()); motionType = motionJson.value("motion",
//     "N/A"); std::vector<nlohmann::json> children =
//     motionJson.value("children",
//     nlohmann::json::array()).get<std::vector<nlohmann::json>>();
//     for(nlohmann::json motionToAdd : children){
//         std::string motionType = motionToAdd.value("behavior",
//         motionJson.value("type", "N/A")); GenericSensor* leftSensor =
//         nullptr; GenericSensor* rightSensor = nullptr; nlohmann::json pos =
//         data.value("position", nlohmann::json({0,0,0})); nlohmann::json dir =
//         data.value("direction", nlohmann::json({0,0,0})); Vector3
//         posV(pos[0], pos[1], pos[2]); Vector3 dirV = Vector3(dir[0], dir[1],
//         dir[2]).Normalized(); Motion* movement = nullptr; if(motionType ==
//         "fear" ||
//             motionType =="explore" ||
//             motionType == "love" ||
//             motionType == "aggression"){
//             std::string entityTarget = motionToAdd.value("target", "light");
//             leftSensor =
//             new GenericSensor(entityTarget, arena, (posV), (dirV),
//             data["radius"], 40); rightSensor = new
//             GenericSensor(entityTarget, arena, (posV), (dirV),
//             data["radius"], -40); leftSensor->SetId(entityId);
//             rightSensor->SetId(entityId);
//             movement = new BraitenbergMotion(motionType, arenaWidth,
//             arenaWidth, data, leftSensor, rightSensor);
//         }else{
//             motionType = motionToAdd.value("type", "default");
//             movement = new SimpleMotion(motionType, arenaWidth, arenaHeight,
//             data);
//         }
//         sensors.push_back(leftSensor);
//         sensors.push_back(rightSensor);
//         motions.push_back(movement);
//     }
// }

// CompositeMotion::~CompositeMotion(){
//         for(GenericSensor* sensorToDel : sensors){
//             delete sensorToDel;
//         }
//         for(Motion* motionToDel : motions){
//             delete motionToDel;
//         }
// }

// void CompositeMotion::Composite(double dt, Vector3& pos, Vector3& vel,
// Vector3& dir){
//     if(motionIndex >= motions.size()){
//         motionIndex = 0;
//     }
//     motions[motionIndex++]->Update(dt, pos, vel, dir);
// }

// void CompositeMotion::ClosestSwitch(double dt, Vector3& pos, Vector3& vel,
// Vector3& dir){

// }

// void CompositeMotion::Weighted(double dt, Vector3& pos, Vector3& vel,
// Vector3& dir){

// }

// void CompositeMotion::Update(double dt, Vector3& pos, Vector3& vel, Vector3&
// dir){
//     motion->Update(dt, pos, vel, dir);
// }