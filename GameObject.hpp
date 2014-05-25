#ifndef _GAME_OBJECT_HPP_
#define _GAME_OBJECT_HPP_

#include <vector>
#include "glm/glm.hpp"

static int id_incr_ = 1;

class GameObjectID {
 public:
  GameObjectID() : id(id_incr_++) {}
  bool operator<(const GameObjectID& other) { return id < other.id; }
  const int id;
};

#include "GameObjectPositionUpdateSubscriber.hpp"

class GameObject {
 public:
  GameObject();
  void addPositionUpdateSubscriber(GameObjectPositionUpdateSubscriber* newSubscriber);

  virtual void setPosition(const glm::vec3& newPosition);

  virtual void setRotation(const glm::vec3& newRotationAxis, float newRotationAmount);

 protected:
  std::vector<GameObjectPositionUpdateSubscriber*> position_update_subscribers_;
  glm::vec3 position_, rotation_axis_;
  float rotation_amt_;
  GameObjectID id_;
};

#endif  // _GAME_OBJECT_HPP_