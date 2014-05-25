#ifndef _GAME_OBJECT_POSITION_UPDATE_SUBSCRIBER_
#define _GAME_OBJECT_POSITION_UPDATE_SUBSCRIBER_

#include "glm/glm.hpp"
#include "GameObject"

class GameObjectPositionUpdateSubscriber {
 public:
  virtual notifyGameObjectPositionUpdated(const GameObjectID& id, glm::vec3 newPosition) = 0;
  virtual notifyGameObjectRotationUpdated(const GameObjectID& id, glm::vec3 newRotation) = 0;
};

#endif  // _GAME_OBJECT_POSITION_UPDATE_SUBSCRIBER_