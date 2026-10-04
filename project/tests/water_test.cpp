// #include "gtest/gtest.h"
// #include "sim/SimulationModel.h"

// class WaterTest : public ::testing::Test {
//  public:
//   void SetUp() { model = new SimulationModel(); }

//   void TearDown() { delete model; }

//  protected:
//   ISimulationModel* model;
// };

// TEST_F(WaterTest, CreateWater) {
//   std::string waterData =
//       "{\"type\":\"water\","
//       "\"image\":\"/assets/sprites/water.png\","
//       "\"motion\":{\"type\":\"none\"},"
//       "\"position\":[200.0,400.0,0],"
//       "\"direction\":[1.0,0.0,0],"
//       "\"radius\":50.0}";

//   json data = json::parse(waterData);
//   IEntity* entity = model->CreateEntity(data);

//   ASSERT_TRUE(entity);
//   EXPECT_DOUBLE_EQ(entity->GetPosition()[0], 200.0);
//   EXPECT_DOUBLE_EQ(entity->GetPosition()[1], 400.0);
//   EXPECT_DOUBLE_EQ(entity->GetRadius(), 50.0);

//   delete entity;
// }