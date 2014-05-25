#ifndef _GAME_PHYSICS_OBJECT_HPP_
#define _GAME_PHYSICS_OBJECT_HPP_

#include "GameObject.hpp"
#include "GamePhysicsState.hpp"

class GamePhysicsObject : public GameObject {
 public:
  virtual GamePhysicsObject(GamePhysicsState* physicsState);

  virtual void setFixedPosition(bool isFixed);

 private:
  GamePhysicsState* state_;
};

#endif  // _GAME_PHYSICS_OBJECT_HPP_