#ifndef _GAME_PHYSICS_STATE_HPP_
#define _GAME_PHYSICS_STATE_HPP_

#include "btBulletDynamicsCommon.h"

class GamePhysicsState {
 public:
  GamePhysicsState();
 private:
  btBroadphaseInterface* broadphase_;
  btCollisionDispatcher dispatcher_;
  btConstraintSolver solver_;
  btDefaultCollisionConfiguration* collision_configuration_;
};

#endif  // _GAME_PHYSICS_STATE_HPP_