#include "ModelInstance.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

#define DEFAULT_POS   vec3(0,0,0)
#define DEFAULT_SCALE vec3(1,1,1)
#define DEFAULT_ROT   vec3(1,0,0)
#define DEFAULT_ROTA  0

using namespace glm;

ModelInstance::ModelInstance(Model *model) :
  pos_        (DEFAULT_POS),
  scale_      (DEFAULT_SCALE),
  rot_        (DEFAULT_ROT),
  rot_amount_ (DEFAULT_ROTA)
{
  model_ = model;
  shader_ids_ = new std::vector<ShaderInstance>();
  build_matrix();
}

ModelInstance::ModelInstance(Model *model, int shaderId) :
  pos_        (DEFAULT_POS),
  scale_      (DEFAULT_SCALE),
  rot_        (DEFAULT_ROT),
  rot_amount_ (DEFAULT_ROTA)
{
  model_ = model;
  shader_ids_ = new std::vector<ShaderInstance>();
  add_shader(shaderId);
  build_matrix();
}

ModelInstance::~ModelInstance() {
  delete shader_ids_;
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

Model *ModelInstance::get_model() {
  return model_;
}

const std::vector<ShaderInstance> *ModelInstance::get_shader_ids() {
  return shader_ids_;
}

void ModelInstance::build_matrix() {
  matrix_ = rotate(scale(translate(mat4(1.0f), pos_), scale_), rot_amount_, rot_);
}

const glm::mat4 ModelInstance::getModelMatrix() const {
  return matrix_;
}

void ModelInstance::add_shader(int shader_id) {
  ShaderInstance newShader = {shader_id, true};
  shader_ids_->push_back(newShader);
}

void ModelInstance::enable_shader(int shader_id) {
  for (auto shader_instance : *shader_ids_) {
    if (shader_instance.shader_id == shader_id)
      shader_instance.enabled = true;
  }
}

void ModelInstance::disable_shader(int shader_id) {
  for (auto shader_instance : *shader_ids_) {
    if (shader_instance.shader_id == shader_id)
      shader_instance.enabled = false;
  }
}
