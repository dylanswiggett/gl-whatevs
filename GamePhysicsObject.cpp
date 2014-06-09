#include "btBulletDynamicsCommon.h"
#include "GamePhysicsObject.hpp"
#include "GamePhysicsState.hpp"
#include "GameObject.hpp"
#include "glm/glm.hpp"

GamePhysicsObject::GamePhysicsObject(GamePhysicsState* physicsState,
    btCollisionShape *shape, double mass_amt, glm::vec3 position) : GameObject() {
  state_ = physicsState;
  // TODO: Register the new game physics object with the physics state.
  btTransform groundTransform;
  groundTransform.setIdentity();
  groundTransform.setOrigin(btVector3(position.x, position.y, position.z));

  btScalar mass(mass_amt);

  btVector3 localInertia(0,0,0);

  shape_->calculateLocalInertia(mass, localInertia);

  // TODO: Extend this so we can update the object position.
  motion_state_ = new btDefaultMotionState(groundTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,motion_state_,shape,localInertia);

  body_ = new btRigidBody(rbInfo);

  state_->addRigidBody(body_);
}

GamePhysicsObject::~GamePhysicsObject() {

}

void GamePhysicsObject::setPositionFixed(bool isFixed) {
  is_fixed_ = isFixed;

  /* TODO: DO THE REST! */
}

void GamePhysicsObject::setPosition(const glm::vec3& newPosition) {
  GameObject::setPosition(newPosition);
}

void GamePhysicsObject::setRotation(const glm::vec3& newRotationAxis, float newRotationAmount) {
  GameObject::setRotation(newRotationAxis, newRotationAmount);
}
