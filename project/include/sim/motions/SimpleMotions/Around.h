#ifndef team_001_8_project_include_sim_motion_SimpleMotions_Around_H_
#define team_001_8_project_include_sim_motion_SimpleMotions_Around_H_

#include "sim/motions/Interfaces/IndividualMotionI.h"

class Around : public IndividualMotionI {
 public:
  /**
   * @brief Constructor for the Around motion.
   * @param data Json that contains metadata about the entity.
   */
  Around(const nlohmann::json& data);

  /**
   * @brief This will move an entity given the arguments
   *        with the descriped motion.
   * @param dt   The delta time is the change in time between each call.
   * @param pos  Current position of the entity to be changed.
   * @param vel  Current velocity of the entity to be changed.
   * @param dir  Current direction of the entity to be changed.
   */
  virtual void Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir);

 private:
  // Scalar speed of the rotation.
  double speed;
  // Rotation_center for around movement.
  Vector3 rotation_center;
  // Radius for the around movement.
  double rotation_radius;
  // Angle for the around movement - helper vairable for movement.
  double angle;
  // Boolean used to determine if the the motion is counterclockwise.
  bool counterclockwise;
};

#endif