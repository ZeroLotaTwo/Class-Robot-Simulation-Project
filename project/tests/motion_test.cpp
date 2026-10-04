// #include "gtest/gtest.h"
// #include "sim/motions/SimpleMotions/BackAndForth.h"
// #include "sim/motions/SimpleMotions/Around.h"
// #include "sim/motions/SimpleMotions/BounceMotion.h"
// #include "sim/motions/SimpleMotions/KeyboardMotion.h"
// #include "sim/motions/SimpleMotions/DefaultMotion.h"
// #include "sim/motions/BraitenbergMotion.h"
// #include "sim/motions/SimpleMotion.h"
// #include "sim/Vector3.h"
// #include "json.hpp"
// #include <cmath>

// static nlohmann::json MakeEntity(const nlohmann::json& motionObj,
//                                   double px = 0, double py = 0,
//                                   double radius = 10.0) {
//     return {
//         {"position", {px, py, 0}},
//         {"radius",   radius},
//         {"motion",   motionObj}
//     };
// }

// // Default motion
// class DefaultMotionTest : public testing::Test {
// protected:
//     void SetUp() override {
//         motion = new DefaultMotion("default");
//         pos = Vector3(100, 200, 0);
//         vel = Vector3(0, 0, 0);
//         dir = Vector3(1, 0, 0);
//     }
//     void TearDown() override { delete motion; }

//     DefaultMotion* motion;
//     Vector3 pos, vel, dir;
// };

// TEST_F(DefaultMotionTest, PositionUnchangedAfterUpdate) {
//     Vector3 originalPos = pos;
//     motion->Update(1.0, pos, vel, dir);
//     EXPECT_DOUBLE_EQ(pos[0], originalPos[0]);
//     EXPECT_DOUBLE_EQ(pos[1], originalPos[1]);
// }

// TEST_F(DefaultMotionTest, VelocityUnchangedAfterUpdate) {
//     motion->Update(1.0, pos, vel, dir);
//     EXPECT_DOUBLE_EQ(vel[0], 0.0);
//     EXPECT_DOUBLE_EQ(vel[1], 0.0);
// }

// // Back and forth
// class BackAndForthTest : public testing::Test {
// protected:
//     void SetUp() override {
//         nlohmann::json data = MakeEntity(
//             {{"type","back_and_forth"},
//              {"points", {{0,0,0},{100,0,0}}},
//              {"speed", 50.0}},
//             0, 0);
//         motion = new BackAndForth("back_and_forth", data);
//         pos = Vector3(0, 0, 0);
//         vel = Vector3(0, 0, 0);
//         dir = Vector3(1, 0, 0);
//     }
//     void TearDown() override { delete motion; }

//     BackAndForth* motion;
//     Vector3 pos, vel, dir;
// };

// TEST_F(BackAndForthTest, MovesForwardTowardP1) {
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_GT(pos[0], 0.0);
// }

// TEST_F(BackAndForthTest, VelocityMagnitudeEqualsSpeed) {
//     motion->Update(0.1, pos, vel, dir);
//     double speed = std::sqrt(vel[0]*vel[0] + vel[1]*vel[1]);
//     EXPECT_NEAR(speed, 50.0, 1e-5);
// }

// TEST_F(BackAndForthTest, ReversesDirectionAfterReachingTarget) {
//     // large dt forces overshoot, entity snaps to p1=(100,0)
//     motion->Update(3.0, pos, vel, dir);
//     EXPECT_NEAR(pos[0], 100.0, 1e-5);
//     // next update should reverse toward p2=(0,0)
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_LT(pos[0], 100.0);
// }

// TEST_F(BackAndForthTest, PositionStaysOnAxis) {
//     for (int i = 0; i < 20; ++i) motion->Update(0.1, pos, vel, dir);
//     EXPECT_NEAR(pos[1], 0.0, 1e-5);
// }

// // Around
// class AroundTest : public testing::Test {
// protected:
//     void SetUp() override {
//         // Entity starts at (200,100,0), center=(100,100,0) => radius=100
//         nlohmann::json data = MakeEntity(
//             {{"type","around"},
//              {"center", {100,100,0}},
//              {"speed", 100.0},
//              {"direction","clockwise"}},
//             200, 100);
//         motion = new Around("around", data);
//         pos = Vector3(200, 100, 0);
//         vel = Vector3(0, 0, 0);
//         dir = Vector3(1, 0, 0);
//     }
//     void TearDown() override { delete motion; }

//     Around* motion;
//     Vector3 pos, vel, dir;
// };

// TEST_F(AroundTest, MaintainsRadius) {
//     for (int i = 0; i < 10; ++i) motion->Update(0.05, pos, vel, dir);
//     double dx = pos[0] - 100.0;
//     double dy = pos[1] - 100.0;
//     double r = std::sqrt(dx*dx + dy*dy);
//     EXPECT_NEAR(r, 100.0, 1e-4);
// }

// TEST_F(AroundTest, ClockwiseDecreasesY) {
//     double initY = pos[1];
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_LT(pos[1], initY + 1e-9);
// }

// TEST_F(AroundTest, CounterclockwiseIncreasesY) {
//     nlohmann::json data = MakeEntity(
//         {{"type","around"},{"center",{100,100,0}},
//          {"speed",100.0},{"direction","counterclockwise"}},
//         200, 100);
//     Around* ccw = new Around("around", data);
//     Vector3 p(200,100,0), v(0,0,0), d(1,0,0);
//     ccw->Update(0.1, p, v, d);
//     EXPECT_GT(p[1], 100.0 - 1e-9);
//     delete ccw;
// }

// TEST_F(AroundTest, AngleWrapsCorrectlyOverManySteps) {
//     // Run 1000 steps; no crash means angle wrap logic is stable
//     for (int i = 0; i < 1000; ++i) motion->Update(0.05, pos, vel, dir);
//     SUCCEED();
// }

// // Bounce
// class BounceMotionTest : public testing::Test {
// protected:
//     void SetUp() override {
//         arenaWidth = 800; arenaHeight = 400;
//         nlohmann::json data = MakeEntity(
//             {{"type","bounce"},{"speed",100.0},
//              {"initial_velocity",{1,1,0}}},
//             400, 200, 10.0);
//         motion = new BounceMotion("bounce", arenaWidth, arenaHeight, data);
//         pos = Vector3(400, 200, 0);
//         vel = Vector3(70.71, 70.71, 0);
//         dir = Vector3(0.707, 0.707, 0);
//     }
//     void TearDown() override { delete motion; }

//     BounceMotion* motion;
//     Vector3 pos, vel, dir;
//     double arenaWidth, arenaHeight;
// };

// TEST_F(BounceMotionTest, StaysWithinBoundsOverTime) {
//     for (int i = 0; i < 200; ++i) motion->Update(0.05, pos, vel, dir);
//     EXPECT_GE(pos[0], 10.0);
//     EXPECT_LE(pos[0], arenaWidth - 10.0);
//     EXPECT_GE(pos[1], 10.0);
//     EXPECT_LE(pos[1], arenaHeight - 10.0);
// }

// TEST_F(BounceMotionTest, ReflectsOffRightWall) {
//     pos = Vector3(arenaWidth - 11, 200, 0);
//     vel = Vector3(100, 0, 0);
//     dir = Vector3(1, 0, 0);
//     motion->Update(0.05, pos, vel, dir);
//     EXPECT_LT(vel[0], 0.0);
// }

// TEST_F(BounceMotionTest, ReflectsOffLeftWall) {
//     pos = Vector3(9, 200, 0);
//     vel = Vector3(-100, 0, 0);
//     dir = Vector3(-1, 0, 0);
//     motion->Update(0.05, pos, vel, dir);
//     EXPECT_GT(vel[0], 0.0);
// }

// TEST_F(BounceMotionTest, ReflectsOffTopWall) {
//     pos = Vector3(400, arenaHeight - 9, 0);
//     vel = Vector3(0, 100, 0);
//     dir = Vector3(0, 1, 0);
//     motion->Update(0.05, pos, vel, dir);
//     EXPECT_LT(vel[1], 0.0);
// }

// TEST_F(BounceMotionTest, ReflectsOffBottomWall) {
//     pos = Vector3(400, 9, 0);
//     vel = Vector3(0, -100, 0);
//     dir = Vector3(0, -1, 0);
//     motion->Update(0.05, pos, vel, dir);
//     EXPECT_GT(vel[1], 0.0);
// }

// TEST_F(BounceMotionTest, SpeedPreservedAfterBounce) {
//     pos = Vector3(arenaWidth - 11, 200, 0);
//     vel = Vector3(100, 0, 0);
//     dir = Vector3(1, 0, 0);
//     motion->Update(0.05, pos, vel, dir);
//     double speed = std::sqrt(vel[0]*vel[0] + vel[1]*vel[1]);
//     EXPECT_NEAR(speed, 100.0, 1e-4);
// }

// // Keyboard
// class KeyboardMotionTest : public testing::Test {
// protected:
//     void SetUp() override {
//         arenaWidth = 800; arenaHeight = 400;
//         nlohmann::json data = MakeEntity(
//             {{"type","keyboard"},{"keys",{"w","d","s","a"}},{"speed",50.0}},
//             400, 200, 10.0);
//         motion = new KeyboardMotion("keyboard", arenaWidth, arenaHeight,
//         data); pos = Vector3(400, 200, 0); vel = Vector3(0, 0, 0); dir =
//         Vector3(1, 0, 0);
//     }
//     void TearDown() override { delete motion; }

//     KeyboardMotion* motion;
//     Vector3 pos, vel, dir;
//     double arenaWidth, arenaHeight;
// };

// TEST_F(KeyboardMotionTest, NoKeyPressNoMovement) {
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_DOUBLE_EQ(pos[0], 400.0);
//     EXPECT_DOUBLE_EQ(pos[1], 200.0);
// }

// TEST_F(KeyboardMotionTest, WKeyMovesUp) {
//     motion->KeyDown("w");
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_GT(pos[1], 200.0);
// }

// TEST_F(KeyboardMotionTest, SKeyMovesDown) {
//     motion->KeyDown("s");
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_LT(pos[1], 200.0);
// }

// TEST_F(KeyboardMotionTest, AKeyMovesLeft) {
//     motion->KeyDown("a");
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_LT(pos[0], 400.0);
// }

// TEST_F(KeyboardMotionTest, DKeyMovesRight) {
//     motion->KeyDown("d");
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_GT(pos[0], 400.0);
// }

// TEST_F(KeyboardMotionTest, DiagonalMovementNormalized) {
//     motion->KeyDown("w");
//     motion->KeyDown("d");
//     motion->Update(0.1, pos, vel, dir);
//     double speed = std::sqrt(vel[0]*vel[0] + vel[1]*vel[1]);
//     EXPECT_NEAR(speed, 50.0, 1e-4);
// }

// TEST_F(KeyboardMotionTest, KeyUpStopsMovement) {
//     motion->KeyDown("w");
//     motion->Update(0.1, pos, vel, dir);
//     double y1 = pos[1];
//     motion->KeyUp("w");
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_NEAR(pos[1], y1, 1e-9);
// }

// TEST_F(KeyboardMotionTest, CannotMoveOutOfBoundsRight) {
//     pos = Vector3(arenaWidth - 11, 200, 0);
//     motion->KeyDown("d");
//     for (int i = 0; i < 20; ++i) motion->Update(0.1, pos, vel, dir);
//     EXPECT_LE(pos[0], arenaWidth - 10.0);
// }

// TEST_F(KeyboardMotionTest, CannotMoveOutOfBoundsLeft) {
//     pos = Vector3(11, 200, 0);
//     motion->KeyDown("a");
//     for (int i = 0; i < 20; ++i) motion->Update(0.1, pos, vel, dir);
//     EXPECT_GE(pos[0], 10.0);
// }

// TEST_F(KeyboardMotionTest, CannotMoveOutOfBoundsTop) {
//     pos = Vector3(400, arenaHeight - 11, 0);
//     motion->KeyDown("w");
//     for (int i = 0; i < 20; ++i) motion->Update(0.1, pos, vel, dir);
//     EXPECT_LE(pos[1], arenaHeight - 10.0);
// }

// TEST_F(KeyboardMotionTest, CannotMoveOutOfBoundsBottom) {
//     pos = Vector3(400, 11, 0);
//     motion->KeyDown("s");
//     for (int i = 0; i < 20; ++i) motion->Update(0.1, pos, vel, dir);
//     EXPECT_GE(pos[1], 10.0);
// }

// TEST_F(KeyboardMotionTest, ZAxisAlwaysZero) {
//     motion->KeyDown("w");
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_DOUBLE_EQ(pos[2], 0.0);
//     EXPECT_DOUBLE_EQ(vel[2], 0.0);
// }

// TEST_F(KeyboardMotionTest, OppositeKeysCancel) {
//     motion->KeyDown("w");
//     motion->KeyDown("s");
//     motion->Update(0.1, pos, vel, dir);
//     EXPECT_DOUBLE_EQ(vel[1], 0.0);
// }

// // BV
// class BraitenbergMotionTest : public testing::Test {
// protected:
//     void SetUp() override {
//         arenaWidth = 800; arenaHeight = 400;
//     }

//     BraitenbergMotion* MakeMotion(const std::string& behavior) {
//         nlohmann::json data = {
//             {"radius", 10.0},
//             {"motion", {{"type", behavior}, {"speed", 100.0}, {"maxSpeed",
//             100.0}}}
//         };
//         return new BraitenbergMotion(behavior, arenaWidth, arenaHeight,
//         data);
//     }

//     double arenaWidth, arenaHeight;
// };

// TEST_F(BraitenbergMotionTest, NoCrashWithZeroSensors_Love) {
//     auto* m = MakeMotion("love");
//     Vector3 pos(400,200,0), vel(0,0,0), dir(1,0,0);
//     m->SetSensorValues(0.0, 0.0);
//     EXPECT_NO_THROW(m->Update(0.01, pos, vel, dir));
//     delete m;
// }

// TEST_F(BraitenbergMotionTest, AggressionMovesEntityWithNonzeroSensors) {
//     auto* m = MakeMotion("aggression");
//     Vector3 pos(400,200,0), vel(0,0,0), dir(1,0,0);
//     m->SetSensorValues(50.0, 50.0);
//     m->Update(0.01, pos, vel, dir);
//     double moved = std::sqrt((pos[0]-400)*(pos[0]-400) +
//     (pos[1]-200)*(pos[1]-200)); EXPECT_GT(moved, 0.0); delete m;
// }

// TEST_F(BraitenbergMotionTest, ExploreNoCrashWithSymmetricSensors) {
//     auto* m = MakeMotion("explore");
//     Vector3 pos(400,200,0), vel(0,0,0), dir(1,0,0);
//     m->SetSensorValues(50.0, 50.0);
//     EXPECT_NO_THROW(m->Update(0.05, pos, vel, dir));
//     delete m;
// }

// TEST_F(BraitenbergMotionTest, FearNoCrashWithSymmetricSensors) {
//     auto* m = MakeMotion("fear");
//     Vector3 pos(400,200,0), vel(0,0,0), dir(1,0,0);
//     m->SetSensorValues(50.0, 50.0);
//     EXPECT_NO_THROW(m->Update(0.05, pos, vel, dir));
//     delete m;
// }

// TEST_F(BraitenbergMotionTest, SetSensorValuesAreApplied) {
//     auto* m = MakeMotion("aggression");
//     Vector3 pos1(400,200,0), vel1(0,0,0), dir1(1,0,0);
//     Vector3 pos2(400,200,0), vel2(0,0,0), dir2(1,0,0);
//     // low sensors
//     m->SetSensorValues(1.0, 1.0);
//     m->Update(0.05, pos1, vel1, dir1);
//     double moved1 = std::sqrt((pos1[0]-400)*(pos1[0]-400) +
//     (pos1[1]-200)*(pos1[1]-200));
//     // high sensors
//     m->SetSensorValues(100.0, 100.0);
//     m->Update(0.05, pos2, vel2, dir2);
//     double moved2 = std::sqrt((pos2[0]-400)*(pos2[0]-400) +
//     (pos2[1]-200)*(pos2[1]-200)); EXPECT_GT(moved2, moved1); delete m;
// }

// TEST_F(BraitenbergMotionTest, StaysWithinArenaOverTime) {
//     auto* m = MakeMotion("aggression");
//     Vector3 pos(400,200,0), vel(50,50,0), dir(0.707,0.707,0);
//     m->SetSensorValues(30.0, 30.0);
//     for (int i = 0; i < 300; ++i) m->Update(0.05, pos, vel, dir);
//     EXPECT_GE(pos[0], 0.0);
//     EXPECT_LE(pos[0], arenaWidth);
//     EXPECT_GE(pos[1], 0.0);
//     EXPECT_LE(pos[1], arenaHeight);
//     delete m;
// }

// TEST_F(BraitenbergMotionTest, DefaultBehaviorNoMovement) {
//     auto* m = MakeMotion("unknown_behavior");
//     Vector3 pos(400,200,0), vel(0,0,0), dir(1,0,0);
//     m->SetSensorValues(50.0, 50.0);
//     m->Update(0.1, pos, vel, dir);
//     // default sensor funcs return 0 => both wheels 0 => early return => no
//     movement EXPECT_DOUBLE_EQ(pos[0], 400.0); EXPECT_DOUBLE_EQ(pos[1],
//     200.0); delete m;
// }

// // Simple
// class SimpleMotionTest : public testing::Test {
// protected:
//     void SetUp() override {
//         arenaWidth = 800; arenaHeight = 400;
//     }

//     SimpleMotion* MakeSimpleMotion(const std::string& type,
//                                     const nlohmann::json& motionExtra = {},
//                                     double px = 400, double py = 200) {
//         nlohmann::json motionObj = motionExtra;
//         motionObj["type"] = type;
//         nlohmann::json data = MakeEntity(motionObj, px, py, 10.0);
//         return new SimpleMotion(type, arenaWidth, arenaHeight, data);
//     }

//     double arenaWidth, arenaHeight;
// };

// TEST_F(SimpleMotionTest, CreatesDefaultMotion) {
//     auto* sm = MakeSimpleMotion("default");
//     ASSERT_NE(sm->GetMotion(), nullptr);
//     delete sm;
// }

// TEST_F(SimpleMotionTest, CreatesBackAndForthMotion) {
//     nlohmann::json extra = {{"points",{{0,0,0},{100,0,0}}},{"speed",50.0}};
//     auto* sm = MakeSimpleMotion("back_and_forth", extra);
//     ASSERT_NE(sm->GetMotion(), nullptr);
//     delete sm;
// }

// TEST_F(SimpleMotionTest, CreatesBounceMotion) {
//     nlohmann::json extra = {{"speed",100.0}};
//     auto* sm = MakeSimpleMotion("bounce", extra);
//     ASSERT_NE(sm->GetMotion(), nullptr);
//     delete sm;
// }

// TEST_F(SimpleMotionTest, CreatesAroundMotion) {
//     nlohmann::json motionObj = {
//         {"type","around"},{"center",{400,100,0}},
//         {"speed",50.0},{"direction","clockwise"}
//     };
//     nlohmann::json data = MakeEntity(motionObj, 500, 100, 10.0);
//     auto* sm = new SimpleMotion("around", arenaWidth, arenaHeight, data);
//     ASSERT_NE(sm->GetMotion(), nullptr);
//     delete sm;
// }

// TEST_F(SimpleMotionTest, CreatesKeyboardMotion) {
//     nlohmann::json extra = {{"keys",{"w","d","s","a"}},{"speed",50.0}};
//     auto* sm = MakeSimpleMotion("keyboard", extra);
//     ASSERT_NE(sm->GetMotion(), nullptr);
//     delete sm;
// }

// TEST_F(SimpleMotionTest, UnknownTypeCreatesDefaultMotion) {
//     auto* sm = MakeSimpleMotion("nonexistent_type");
//     ASSERT_NE(sm->GetMotion(), nullptr);
//     delete sm;
// }

// TEST_F(SimpleMotionTest, DelegatesUpdateToBackAndForthChild) {
//     nlohmann::json extra = {{"points",{{0,0,0},{200,0,0}}},{"speed",100.0}};
//     auto* sm = MakeSimpleMotion("back_and_forth", extra, 0, 0);
//     Vector3 pos(0,0,0), vel(0,0,0), dir(1,0,0);
//     sm->Update(0.1, pos, vel, dir);
//     EXPECT_GT(pos[0], 0.0);
//     delete sm;
// }

// TEST_F(SimpleMotionTest, DelegatesUpdateToBounceChild) {
//     nlohmann::json extra = {{"speed",100.0}};
//     auto* sm = MakeSimpleMotion("bounce", extra);
//     Vector3 pos(400,200,0), vel(100,0,0), dir(1,0,0);
//     sm->Update(0.05, pos, vel, dir);
//     // position should have changed
//     EXPECT_NE(pos[0], 400.0);
//     delete sm;
// }

// TEST_F(SimpleMotionTest, DefaultMotionDoesNotMove) {
//     auto* sm = MakeSimpleMotion("default");
//     Vector3 pos(400,200,0), vel(0,0,0), dir(1,0,0);
//     sm->Update(1.0, pos, vel, dir);
//     EXPECT_DOUBLE_EQ(pos[0], 400.0);
//     EXPECT_DOUBLE_EQ(pos[1], 200.0);
//     delete sm;
// }

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }