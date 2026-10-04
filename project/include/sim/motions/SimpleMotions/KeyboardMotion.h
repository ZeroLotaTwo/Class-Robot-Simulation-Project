#ifndef team_001_8_project_include_sim_motion_SimpleMotions_KeyboardMotion_H_
#define team_001_8_project_include_sim_motion_SimpleMotions_KeyboardMotion_H_

#include <set>

#include "sim/motions/Interfaces/IndividualMotionI.h"

class KeyboardMotion : public IndividualMotionI {
 public:
  /**
   * @brief Constructor for the Keyboard motion.
   * @param data Json that contains metadata about the entity.
   */
  KeyboardMotion(double arenaWidth, double arenaHeight,
                 const nlohmann::json& data);

  /**
   * @brief This will move an entity given the arguments
   *        with the descriped motion.
   * @param dt   The delta time is the change in time between each call.
   * @param pos  Current position of the entity to be changed.
   * @param vel  Current velocity of the entity to be changed.
   * @param dir  Current direction of the entity to be changed.
   */
  virtual void Update(double dt, Vector3& pos, Vector3& vel, Vector3& dir);

  // Track currently pressed keys
  std::set<std::string> pressedKeys;

  /**
   * @brief This is used to send which keys have been pressed.
   *        This is primarily for the simulation model.
   * @param key This is for the key that has been pressed down on the keyboard.
   */
  void KeyDown(const std::string& key);

  /**
   * @brief This is used to send which keys have been released.
   *        This is primarily for the simulation model.
   * @param key This is for the key that has been released on the keyboard.
   */
  void KeyUp(const std::string& key);

 private:
  // Scalar speed for movement.
  double speed;
  // Width of arena.
  double arenaWidth;
  // Height of arena.
  double arenaHeight;
  // Radius of the robot for wall collisioins.
  double radius;
  // Character for upwards movement.
  std::string keyUp;
  // Character for right movement.
  std::string keyRight;
  // Character for downwards movement.
  std::string keyDown;
  // Character for left movement.
  std::string keyLeft;
};

#endif