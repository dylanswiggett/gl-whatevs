#ifndef _MODEL_INSTANCE_HPP_
#define _MODEL_INSTANCE_HPP_

#include "glm/glm.hpp"
#include <string>

class ModelInstance {
 public:
  ModelInstance(int modelId, int shaderId);

  int get_model_id();
  int get_shader_id();
 private:
  glm::vec3 pos, scale, rot;
  int model_id_, shader_id_;
};

#endif  // _MODEL_INSTANCE_HPP_