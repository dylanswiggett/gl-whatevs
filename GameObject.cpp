#include "glm/glm.hpp"
#include "GameObject.hpp"
#include "GameObjectPositionUpdateSubscriber.hpp"
#include "GameObjectID.hpp"

GameObject::GameObject() {
  /* ... */
  setRotation(glm::vec3(0,1,0), 0);
}

void GameObject::addPositionUpdateSubscriber(GameObjectPositionUpdateSubscriber* newSubscriber) {
  position_update_subscribers_.push_back(newSubscriber);
}

void GameObject::setPosition(const glm::vec3& newPosition) {
  position_ = newPosition;
  for (auto subscriber : position_update_subscribers_)
    subscriber->notifyGameObjectPositionUpdated(id_, position_);
}

void GameObject::setRotation(const glm::vec3& newRotationAxis, float newRotationAmt) {
  rotation_axis_ = newRotationAxis;
  rotation_amt_ = newRotationAmt;
  for (auto subscriber : position_update_subscribers_)
    subscriber->notifyGameObjectRotationUpdated(id_, rotation_axis_, rotation_amt_);
}