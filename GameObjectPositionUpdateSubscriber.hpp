#ifndef _GAME_OBJECT_POSITION_UPDATE_SUBSCRIBER_
#define _GAME_OBJECT_POSITION_UPDATE_SUBSCRIBER_

#include "glm/glm.hpp"
#include "GameObjectID.hpp"

class GameObjectPositionUpdateSubscriber {
 public:
  virtual void notifyGameObjectPositionUpdated(const GameObjectID& id, glm::vec3 newPosition) = 0;
  virtual void notifyGameObjectRotationUpdated(const GameObjectID& id, glm::vec3 newRotationAxis, float newRotation) = 0;
};

#endif  // _GAME_OBJECT_POSITION_UPDATE_SUBSCRIBER_