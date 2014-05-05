#ifndef MODEL_INSTANCE_HPP_
#define MODEL_INSTANCE_HPP_

#include "GL/glm.h"
#include <string>

class ModelInstance {
 public:
  ModelInstance(int modelId, int shaderId);
  ModelInstance(std::string modelName, std::string shaderId);
 private:
  glm::vec3 pos, scale, rot;
  int modelId;
};

#endif  // MODEL_INSTANCE_HPP_