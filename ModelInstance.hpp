#ifndef _MODEL_INSTANCE_HPP_
#define _MODEL_INSTANCE_HPP_

#include "glm/glm.hpp"
#include <string>

class ModelInstance {
 public:
  ModelInstance(int modelId, int shaderId);

  void setPosition(glm::vec3 newPos);
  void setScale(glm::vec3 newScale);
  void setRotation(glm::vec3 rotAxis, float rotAmount);

  int get_model_id();
  int get_shader_id();

  const glm::mat4 getModelMatrix() const;
 private:
  glm::vec3 pos_, scale_, rot_;
  float rot_amount_;
  int model_id_, shader_id_;
};

#endif  // _MODEL_INSTANCE_HPP_