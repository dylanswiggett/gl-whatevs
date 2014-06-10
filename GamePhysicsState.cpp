#include <iostream>
#include "btBulletDynamicsCommon.h"
#include "GamePhysicsState.hpp"

GamePhysicsState::GamePhysicsState() {
  // Create all of the basic, absolutely necessary bullet physics state.
  collision_configuration_ = new btDefaultCollisionConfiguration();
  dispatcher_ = new btCollisionDispatcher(collision_configuration_);
  broadphase_ = new btDbvtBroadphase();
  solver_ = new btSequentialImpulseConstraintSolver();
  dynamics_world_ = new btDiscreteDynamicsWorld(
    dispatcher_, broadphase_, solver_, collision_configuration_);
}

GamePhysicsState::~GamePhysicsState() {
  delete collision_configuration_;
  delete dispatcher_;
}

void GamePhysicsState::step(float milliseconds) {
  dynamics_world_->stepSimulation(milliseconds / 1000000.f);
}
