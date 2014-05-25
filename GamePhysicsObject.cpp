#include "btBulletDynamicsCommon.h"
#include "GamePhysicsObject.hpp"
#include "GamePhysicsState.hpp"
#include "GameObject.hpp"

GamePhysicsObject::GamePhysicsObject(GamePhysicsState* physicsState) : GameObject() {
  state_ = physicsState;
  // TODO: Register the new game physics object with the physics state.
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
