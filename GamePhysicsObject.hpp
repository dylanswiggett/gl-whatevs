#ifndef _GAME_PHYSICS_OBJECT_HPP_
#define _GAME_PHYSICS_OBJECT_HPP_

#include "GameObject.hpp"
#include "GamePhysicsState.hpp"

class GamePhysicsObject : public GameObject {
 public:
  GamePhysicsObject(GamePhysicsState* physicsState);
  virtual ~GamePhysicsObject();

  virtual void setPositionFixed(bool isFixed);

  virtual void setPosition(const glm::vec3& newPosition);
  virtual void setRotation(const glm::vec3& newRotationAxis, float newRotationAmount);

 private:
  GamePhysicsState* state_;
  bool is_fixed_;
};

#endif  // _GAME_PHYSICS_OBJECT_HPP_