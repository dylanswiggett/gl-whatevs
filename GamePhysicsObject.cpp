#include "btBulletDynamicsCommon.h"
#include "GamePhysicsObject.hpp"
#include "GamePhysicsState.hpp"
#include "GameObject.hpp"
#include "glm/glm.hpp"
#include <iostream>

GamePhysicsObject::GamePhysicsObject(btCollisionShape *shape, double mass_amt) :
    GameObject(), shape_(shape) {
  btTransform groundTransform;
  groundTransform.setIdentity();
  groundTransform.setOrigin(btVector3());

  btScalar mass(mass_amt);

  btVector3 localInertia(0,0,0);

  if (mass_amt != 0.0f) {
    shape_->calculateLocalInertia(mass, localInertia);
  }

  // TODO: Extend this so we can update the object position.
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,this,shape,localInertia);

  body_ = new btRigidBody(rbInfo);

  if (mass_amt == 0.0f)
    setPositionFixed(true);
  else
    setPositionFixed(false);
}

GamePhysicsObject::~GamePhysicsObject() {

}

void GamePhysicsObject::setPositionFixed(bool isFixed) {
  is_fixed_ = isFixed;
  if (isFixed) {
    body_->setCollisionFlags(body_->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    body_->setActivationState(DISABLE_DEACTIVATION);
  } else {
    body_->setCollisionFlags( body_->getCollisionFlags() & ~(btCollisionObject::CF_KINEMATIC_OBJECT));
    body_->activate(true); // or try… body->forceActivationState(ACTIVE_FLAG)
  }
}

void GamePhysicsObject::addToPhysics(GamePhysicsState* physicsState) {
  std::cout << "Adding object to physics simulation." << std::endl;
  physicsState->addRigidBody(body_);
}

void GamePhysicsObject::setPosition(const glm::vec3& newPosition) {
  GameObject::setPosition(newPosition);
  btTransform transform = body_->getCenterOfMassTransform();
  transform.setOrigin(
    btVector3(newPosition.x, newPosition.y, newPosition.z));
  body_->setCenterOfMassTransform(transform);
}

void GamePhysicsObject::setRotation(const glm::vec3& newRotationAxis, float newRotationAmt) {
  GameObject::setRotation(newRotationAxis, newRotationAmt);
  setPositionFixed(true);
}

// Allow seamless interaction with the physics engine.

void GamePhysicsObject::getWorldTransform(btTransform &worldTrans) const {
  worldTrans = btTransform(
    btQuaternion(
      btVector3(rotation_axis_.x, rotation_axis_.y, rotation_axis_.z),
      rotation_amt_),
    btVector3(position_.x, position_.y, position_.z));

  // std::cout << "Getting world position at " << worldTrans.getOrigin().getY() << std::endl;
}

void GamePhysicsObject::setWorldTransform(const btTransform &worldTrans) {
  btVector3 originTrans = worldTrans.getOrigin();
  btQuaternion rot = worldTrans.getRotation();
  btVector3 rot_axis = rot.getAxis();
  btScalar rot_angle = rot.getAngle();

  GameObject::setPosition(glm::vec3(originTrans.getX(), originTrans.getY(), originTrans.getZ()));
  GameObject::setRotation(glm::vec3(rot_axis.getX(), rot_axis.getY(), rot_axis.getZ()), rot_angle);
  // std::cout << "Setting world position to " << worldTrans.getOrigin().getY() << std::endl;
}