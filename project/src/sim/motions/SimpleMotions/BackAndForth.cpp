#include "sim/motions/SimpleMotions/BackAndForth.h"

BackAndForth::BackAndForth(const nlohmann::json& data) {
  nlohmann::json motion = data.value("motion", nlohmann::json::object());
  speed = motion.value("speed", 0.0);
  std::vector<std::vector<double>> points =
      motion.value("points", std::vector<std::vector<double>>());
  if (points.empty()) {
    p1 = Vector3(0, 0, 0);
    p2 = Vector3(0, 0, 0);
  } else {
    p1 = Vector3(points[0][0], points[0][1], points[0][2]);
    p2 = Vector3(points[1][0], points[1][1], points[1][2]);
  }
  this->target = this->p1;  // default to start moving towards p1
}

void BackAndForth::Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir) {
  Vector3 toTarget = target - pos;
  double distance = toTarget.Length();
  dir = toTarget.Normalized();
  vel = dir * speed;

  // check if we will overshoot on next update
  if (distance < speed * dt) {
    pos = target;
    target = (target[0] == p1[0] && target[1] == p1[1]) ? p2 : p1;
    return;
  }
  // move
  pos = pos + vel * dt;
}
