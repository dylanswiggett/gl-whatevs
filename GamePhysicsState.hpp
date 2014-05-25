#ifndef _GAME_PHYSICS_STATE_HPP_
#define _GAME_PHYSICS_STATE_HPP_

#include "btBulletDynamicsCommon.h"

// Stores all of the overarching physics state in-game.
// Basically a wrapper for all of the essential bullet physics
// functionality.
class GamePhysicsState {
 public:
  GamePhysicsState();
  ~GamePhysicsState();

  void step(float milliseconds);
 private:
  btBroadphaseInterface* broadphase_;
  btCollisionDispatcher* dispatcher_;
  btConstraintSolver* solver_;
  btDefaultCollisionConfiguration* collision_configuration_;
  btDiscreteDynamicsWorld* dynamics_world_;
};

#endif  // _GAME_PHYSICS_STATE_HPP_