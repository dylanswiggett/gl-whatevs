#ifndef _MODEL_INSTANCE_POSITION_UPDATER_HPP_
#define _MODEL_INSTANCE_POSITION_UPDATER_HPP_

#include "GameObjectPositionUpdateSubscriber.hpp"
#include "GameObjectID.hpp"

// Subscribes to a GameObject. When the object has its position
// or rotation changed, this will apply the corresponding changes
// to a ModelInstance, propogating these changes to the graphics
// pipeline.
class ModelInstancePositionUpdater : GameObjectPositionUpdateSubscriber {
 public:
  ModelInstancePositionUpdater(ModelInstance* instance) {
    /* ... */
  }

  virtual void notifyGameObjectPositionUpdated(const GameObjectID& id, glm::vec3 newPosition) {
    instance->setPosition(newPosition);
  }

  virtual void notifyGameObjectRotationUpdated(const GameObjectID& id, glm::vec3 newRotationAxis, float newRotation) {
    instance->setRotation(newRotationAxis, newRotation);
  }

 private:
  ModelInstance* instance;
};

#endif  // _MODEL_INSTANCE_POSITION_UPDATER_HPP_