#ifndef _MODEL_INSTANCE_HPP_
#define _MODEL_INSTANCE_HPP_

#include "GL/glm.h"
#include <string>

class ModelInstance {
 public:
  ModelInstance(int modelId, int shaderId);
  ModelInstance(std::string modelName, std::string shaderId);

  int get_model_id();
  int get_shader_id();
 private:
  glm::vec3 pos, scale, rot;
  int modelId;
};

#endif  // _MODEL_INSTANCE_HPP_