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
}

void ModelInstance::setPosition(glm::vec3 newPos) {
  pos_ = newPos;
}

void ModelInstance::setScale(glm::vec3 newScale) {
  scale_ = newScale;
}

void ModelInstance::setRotation(glm::vec3 rotAxis, float rotAmount) {
  rot_ = rotAxis;
  rot_amount_ = rotAmount;
}

int ModelInstance::get_model_id() {
  return model_id_;
}

int ModelInstance::get_shader_id() {
  return shader_id_;
}

const glm::mat4 ModelInstance::getModelMatrix() const {
  mat4 id = mat4(1.0f);
  mat4 modelMat = mat4(1.0f);
  modelMat *= scale(id, scale_);
  modelMat *= rotate(id, rot_amount_, rot_);
  modelMat *= translate(id, pos_);
  return modelMat;
}