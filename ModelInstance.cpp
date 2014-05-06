#include "ModelInstance.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

ModelInstance::ModelInstance(int modelId, int shaderId) :
  pos_(vec3(0, 0, 0)),
  scale_(vec3(1, 1, 1)),
  rot_(vec3(1, 0, 0)),
  rot_amount_(0)
{
  model_id_ = modelId;
  shader_id_ = shaderId;
  build_matrix();
}

void ModelInstance::setPosition(glm::vec3 newPos) {
  pos_ = newPos;
  build_matrix();
}

void ModelInstance::setScale(glm::vec3 newScale) {
  scale_ = newScale;
  build_matrix();
}

void ModelInstance::setRotation(glm::vec3 rotAxis, float rotAmount) {
  rot_ = rotAxis;
  rot_amount_ = rotAmount;
  build_matrix();
}

int ModelInstance::get_model_id() {
  return model_id_;
}

int ModelInstance::get_shader_id() {
  return shader_id_;
}

void ModelInstance::build_matrix() {
  matrix_ = rotate(scale(translate(mat4(1.0f), pos_), scale_), rot_amount_, rot_);
}

const glm::mat4 ModelInstance::getModelMatrix() const {
  return matrix_;
}