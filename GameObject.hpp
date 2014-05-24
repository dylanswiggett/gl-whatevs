#ifndef _GAME_OBJECT_HPP_
#define _GAME_OBJECT_HPP_

#include "ModelInstance.hpp"
#include "GameObjectPositionUpdateSubscriber.cpp"
#include "glm/glm.hpp"

class GameObjectID {
 public:
  GameObjectID() : id(id_incr_++) {}
  const int id;
 private:
  static id_incr_ = 1;
};

class GameObject {
 public:
  virtual GameObject();
  virtual addPositionUpdateSubscriber(const GameObjectPositionUpdateSubscriber& newSubscriber);

 protected:
  glm::vec3 position_, rotation_;
};

#endif  // _GAME_OBJECT_HPP_