#ifndef _GAME_PHYSICS_OBJECT_HPP_
#define _GAME_PHYSICS_OBJECT_HPP_

#include "btBulletDynamicsCommon.h"
#include "GameObject.hpp"
#include "GamePhysicsState.hpp"
#include "glm/glm.hpp"

class GamePhysicsObject : public GameObject {
 public:
  GamePhysicsObject(GamePhysicsState* physicsState,
    btCollisionShape *shape, double mass, glm::vec3 position);
  virtual ~GamePhysicsObject();

  virtual void setPositionFixed(bool isFixed);

  virtual void setPosition(const glm::vec3& newPosition);
  virtual void setRotation(const glm::vec3& newRotationAxis, float newRotationAmount);

 private:
  GamePhysicsState* state_;

  btCollisionShape* shape_;
  btDefaultMotionState* motion_state_;
  btRigidBody* body_;

  bool is_fixed_;
};

#endif  // _GAME_PHYSICS_OBJECT_HPP_