#ifndef _GAME_OBJECT_HPP_
#define _GAME_OBJECT_HPP_

#include <vector>
#include "GameObjectPositionUpdateSubscriber.cpp"
#include "glm/glm.hpp"

class GameObjectID {
 public:
  GameObjectID() : id(id_incr_++) {}
  bool operator<(const GameObjectID& other) { return id < other.id }
  const int id;
 private:
  static id_incr_ = 1;
};

class GameObject {
 public:
  virtual GameObject();
  virtual addPositionUpdateSubscriber(GameObjectPositionUpdateSubscriber* newSubscriber) {
    position_update_subscribers_.push_back(newSubscriber);
  }

  void setPosition(const glm::vec3& newPosition) {
    position_ = newPosition;
    for (auto subscriber : position_update_subscribers_)
      subscriber->notifyGameObjectPositionUpdated(id, position_);
  }

  void setRotation(const glm::vec3& newPosition) {
    rotation_ = newRotation;
    for (auto subscriber : position_update_subscribers_)
      subscriber->notifyGameObjectRotationUpdated(id, rotation_);
  }

 protected:
  std::vector<GameObjectPositionUpdateSubscriber*> position_update_subscribers_;
  glm::vec3 position_, rotation_;
  GameObjectID id_;
};

#endif  // _GAME_OBJECT_HPP_