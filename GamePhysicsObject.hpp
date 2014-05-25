#ifndef _GAME_PHYSICS_OBJECT_HPP_
#define _GAME_PHYSICS_OBJECT_HPP_

#include "GameObject.hpp"

class GamePhysicsObject : public GameObject {
 public:
  virtual GamePhysicsObject();
  virtual setModelInstance(ModelInstance* instance);

 private:
  ModelInstance* model_instance_;
  glm::vec3 
};

#endif  // _GAME_PHYSICS_OBJECT_HPP_