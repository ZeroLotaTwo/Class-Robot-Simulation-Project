// No time to do this

#ifndef team_001_8_project_include_sim_motion_CompositeMotin_H_
#define team_001_8_project_include_sim_motion_CompositeMotin_H_
class CompositeMotion {};

// #include "sim/motions/SimpleMotion.h"
// #include "sim/motions/BraitenbergMotion.h"

// class Vector3;

// class CompositeMotion : public Motion {
//     public:
//     CompositeMotion(const ISimulationModel& arena, std::string motionType,
//     int entityId, double arenaWidth, double arenaHeight, const
//     nlohmann::json& data);

//     virtual ~CompositeMotion();

//     virtual void Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir)
//     override;

//     private:
//     // Motion* motion = nullptr;
//     std::vector<GenericSensor*> sensors;
//     std::vector<Motion*> motions;

//     int motionIndex = 0;
//     void Composite(double dt, Vector3& pos, Vector3& vel, Vector3& dir);
//     void ClosestSwitch(double dt, Vector3& pos, Vector3& vel, Vector3& dir);
//     void Weighted(double dt, Vector3& pos, Vector3& vel, Vector3& dir);
// };

#endif
