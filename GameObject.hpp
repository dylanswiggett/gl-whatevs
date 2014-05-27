#ifndef _GAME_OBJECT_HPP_
#define _GAME_OBJECT_HPP_

#include <vector>
#include "glm/glm.hpp"
#include "GameObjectPositionUpdateSubscriber.hpp"
#include "GameObjectID.hpp"

class GameObject {
 public:
  GameObject();
  
  void addPositionUpdateSubscriber(GameObjectPositionUpdateSubscriber* newSubscriber);

  virtual void setPosition(const glm::vec3& newPosition);

  virtual void setRotation(const glm::vec3& newRotationAxis, float newRotationAmount);

  GameObjectID getID() {
    return id_;
  }

 protected:
  std::vector<GameObjectPositionUpdateSubscriber*> position_update_subscribers_;
  glm::vec3 position_, rotation_axis_;
  float rotation_amt_;
  GameObjectID id_;
};

#endif  // _GAME_OBJECT_HPP_