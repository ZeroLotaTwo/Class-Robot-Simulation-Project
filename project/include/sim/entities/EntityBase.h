/**
 * @file EntityBase.h
 *
 * @copyright 2026 3081 Staff, All rights reserved.
 */

#ifndef team_001_8_project_include_sim_entities_EntityBase_H_
#define team_001_8_project_include_sim_entities_EntityBase_H_

#include "core/IEntity.h"
#include "sim/Vector3.h"
#include "sim/motions/Motion.h"

/**
 * @brief EntityBase is a base class that has basic functionality that is shared
 * across entities.
 */

class EntityBase : public IEntity {
 public:
  /**
   * @brief Default constructor.
   */
  EntityBase();

  /**
   * @brief Virtual destructor; enables polymorphic destructors.
   */
  virtual ~EntityBase();

  /**
   * @brief Gets the name.
   * @return The entity's name.
   */
  virtual const std::string& GetName() const { return name; }

  /**
   * @brief Gets the unique entity id.
   * @return The entity's unique identifier.
   */
  virtual int GetId() const { return id; }

  /**
   * @brief Gets the entity's position.
   * @return Pointer to array of 3 doubles (x, y, z).
   */
  virtual const double* GetPosition() const { return pos.GetArray(); }

  /**
   * @brief Gets the entity's direction as a unit vector with 3 components.
   * @return Pointer to array of 3 doubles (x, y, z).
   */
  virtual const double* GetDirection() const { return dir.GetArray(); }

  /**
   * @brief Gets the entity's current speed.
   * @return The current speed value.
   */
  virtual double GetSpeed() const { return speed; }

  /**
   * @brief Gets the entity's radius.
   * @return The radius value.
   */
  virtual double GetRadius() const { return radius; }

  /**
   * @brief Updates the entity based on a timestep.
   * @param dt A delta timestep from the last update.
   */
  virtual void Update(double dt) {}

  /**
   * @brief Returns information about the specific C++ type of entity.
   * This is used to efficiently check types rather than dynamic casting.
   * @return Reference to the type_info for this entity's type.
   */
  const std::type_info& GetType() const { return *type; }
  // string classifying the movement.
  std::string motion;
  // member variable used by all entities to describe their movement.
  Motion* movement;

 protected:
  /**
   * @brief Sets the entity's type for runtime type checking.
   * @param typeName Human-readable name for the type.
   */
  template <typename T>
  void SetType(const std::string& typeName, T* currentObject) {
    static const std::type_info& type = typeid(T);
    this->type = &type;
    this->typeName = typeName;
    this->currentObject = this;
    this->name = typeName + " " + std::to_string(id);
  }

  template <typename T>
  void SetType(const std::string& typeName) {
    static const std::type_info& type = typeid(T);
    this->type = &type;
    this->typeName = typeName;
    this->currentObject = currentObject;
    this->name = typeName + " " + std::to_string(id);
  }

  /**
   * @brief Gets the human-readable type name.
   * @return The entity's type name string.
   */
  virtual const std::string& GetTypeName() const { return typeName; }

  IEntity* GetInstance() { return currentObject; }

 private:
  int id;
  const std::type_info* type;
  std::string typeName;
  IEntity* currentObject;

 protected:
  std::string name;
  Vector3 pos;
  Vector3 dir;
  double speed;
  double radius;
};

#endif