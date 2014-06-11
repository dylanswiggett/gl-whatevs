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

// Allow seamless interaction with the physics engine.

void GamePhysicsObject::getWorldTransform(btTransform &worldTrans) const {
  worldTrans = btTransform(
    btQuaternion(
      btVector3(rotation_axis_.x, rotation_axis_.y, rotation_axis_.z),
      rotation_amt_),
    btVector3(position_.x, position_.y, position_.z));
}

void GamePhysicsObject::setWorldTransform(const btTransform &worldTrans) {
  btVector3 originTrans = worldTrans.getOrigin();
  btQuaternion rot = worldTrans.getRotation();
  btVector3 rot_axis = rot.getAxis();
  btScalar rot_angle = rot.getAngle();

  setPosition(glm::vec3(originTrans.getX(), originTrans.getY(), originTrans.getZ()));
  setRotation(glm::vec3(rot_axis.getX(), rot_axis.getY(), rot_axis.getZ()), rot_angle);
}