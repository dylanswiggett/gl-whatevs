#ifndef _MODEL_INSTANCE_HPP_
#define _MODEL_INSTANCE_HPP_

#include "glm/glm.hpp"
#include <string>

class ModelInstance {
 public:
  // TODO: ModelInstance(int modelId);
  ModelInstance(int modelId, int shaderId);

  void setPosition(glm::vec3 newPos);
  void setScale(glm::vec3 newScale);
  void setRotation(glm::vec3 rotAxis, float rotAmount);

  int get_model_id();
  int get_shader_id();

  // TODO: add_shader(int shader_id_);
  // TODO: enable_shader(int shader_id_);
  // TODO: disable_shader(int shader_id_);

  const glm::mat4 getModelMatrix() const;
 private:
  void build_matrix();

  // TODO: Store a pointer to the model rather than a modelId.

  glm::vec3 pos_, scale_, rot_;
  glm::mat4 matrix_;
  float rot_amount_;
  int model_id_, shader_id_;
};

#endif  // _MODEL_INSTANCE_HPP_