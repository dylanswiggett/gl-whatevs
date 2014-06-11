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

  shape_->calculateLocalInertia(mass, localInertia);

  // TODO: Extend this so we can update the object position.
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,this,shape,localInertia);

  body_ = new btRigidBody(rbInfo);
}

GamePhysicsObject::~GamePhysicsObject() {

}

void GamePhysicsObject::setPositionFixed(bool isFixed) {
  is_fixed_ = isFixed;

  /* TODO: DO THE REST! */
}

void GamePhysicsObject::addToPhysics(GamePhysicsState* physicsState) {
  physicsState->addRigidBody(body_);
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