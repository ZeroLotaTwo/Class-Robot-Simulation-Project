// #include "gtest/gtest.h"
// #include "sim/SimulationModel.h"
// #include "sim/sensors/GenericSensor.h"
// // #include "json.hpp"
// // class ExampleTest : public ::testing::Test {
// // public:
// //   void SetUp() {
// //     model = new SimulationModel();
// //   }

// //   void TearDown() {
// //     delete model;
// //   }
// // protected:

// //   ISimulationModel* model;
// // };

// std::string typeIdToString(std::string type){
//   std::string typeName = "";
//   for(char chr : type){
//     if(chr < '0' || chr > '9'){
//       typeName += chr;
//     }
//   }
//   if(typeName == "EnergyEntity"){
//     typeName = "energy";
//   }else if(typeName == "Light"){
//     typeName = "light";
//   }else if(typeName == "BraitenbergVehicle"){
//     typeName = "bv";
//   }else if(typeName == "Robot"){
//     typeName = "robot";
//   }else if(typeName == "Water"){
//     typeName = "water";
//   }else if(typeName == "Predator"){
//     typeName = "predator";
//   }
// }

// // This fixture does not have an entity to ignore.
// template<typename T>
// class SensorTest : public::testing::Test{
// public:
//     voidSetUp(){
//       model = new SimulationModel();
//       Vector3 pos = Vector3(0,0,0);
//       Vector3 dir = Vector3(1,0,0);
//       double radius = 0;
//       double degress = 0;
//       std::string type = typeid(T).name();
//       std::string typeName = typeIdToString(type);
//       sensor = new GenericSensor(typeName, -1, model, pos, dir, radius,
//       degrees);
//     }

//     void TearDown(){
//       delete sensor;
//       delete model;
//     }

// protected:
//   Vector3 pos = Vector3(0,0,0);
//   Vector3 dir = Vector3(1,0,0);
//   double radius = 0;
//   double degress = 0;
//   GenericSensor<T>* sensor;
//   ISimulationModel* model;
// };

// using EntityTypes = ::testing::Types
// <Light, EnergyEntity, Robot, Predator, BraitenbergVehicle, Water>;

// std::vector<std::string> typeNames;
// for(int i = 0; i < 6; i++){

// }

// TYPED_TEST_SUITE(SensorTest, EntityTypes);

// /*
// // This the formula descriped in iter1
// // std::max(1800.0/std::pow(1.08, (closest light position - sensor
// position).Length()), 0.0001)
// // For this test since we are comparing doubles we can't compare exactly
// and need an epsilon which is our error tolerance
// // And so if it is equal we can abs(val1 - val2) <= epsilon
// // And to test if not equal we can abs(val1 - val2) >= epsilon
// */
// TYPED_TEST(SensorTest, GetSensorValueTest){
//   std::string type = typeid(TypeParam).name();
//   std::string typeName = typeIdToString(type);
// json data1 = {
//     {"type", "light"},
//     {"image", "/assets/sprites/light.png"},
//     {"motion", {
//         {"type", "around"},
//         {"center", {900.0, 250.0, 0.0}},
//         {"radius", 100.0},
//         {"speed", 100.0}
//     }},
//     {"position", {1000.0, 250.0, 0.0}},
//     {"direction", {-1.0, 0.0, 0.0}},
//     {"radius", 50.0}
// };
// // This robot is closer than light above
// json data2 = {
//     {"type", "robot"},
//     {"image", "/assets/sprites/light.png"},
//     {"motion", {
//         {"type", "default"}
//     }},
//     {"position", {10.0, 10.0, 0.0}},
//     {"direction", {-1.0, 0.0, 0.0}},
//     {"radius", 50.0}
// };

// json data3 = {
//     {"type", "light"},
//     {"image", "/assets/sprites/light.png"},
//     {"motion", {
//         {"type", "around"},
//         {"center", {50.0, 50.0, 0.0}},
//         {"radius", 100.0},
//         {"speed", 100.0}
//     }},
//     {"position", {1000.0, 250.0, 0.0}},
//     {"direction", {-1.0, 0.0, 0.0}},
//     {"radius", 50.0}
// };

//   model->CreateEntity(data1);

//   double val = sensor->GetSensorValue();
//   Vector3 lightPos = Vector3(1000, 250, 0);
//   double expectedVal = std::max(1800.0/std::pow(1.08, (lightPos -
//   pos).Length()), 0.0001); double epsilon = 1e-5; EXPECT_LE(abs(val -
//   expectedVal), epsilon); double dt = 0.1; for(int i = 0; i < 1; i += dt){
//     model->Update(dt);
//   }
//   EXPECT_GE(abs(val - sensor->GetSensorValue()), epsilon);

//   model->CreateEntity(data2);
//   // Should not have changed b/c it is a different entity
//   EXPECT_LE(abs(val - sensor->GetSensorValue()), epsilon);

//   model->CreateEntity(data3);
//   EXPECT_GE(abs(val - sensor->GetSensorValue()), epsilon);
// }

// TEST_F(LightSensorTest, GetDistTest){

// }