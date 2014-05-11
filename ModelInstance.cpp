#include "ModelInstance.hpp"

#define GLM_FORCE_RADIANS

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
  graphics_ids_ = new std::vector<GraphicsInstance>();
  build_matrix();
}

ModelInstance::ModelInstance(Model *model, int shaderId) :
  pos_        (DEFAULT_POS),
  scale_      (DEFAULT_SCALE),
  rot_        (DEFAULT_ROT),
  rot_amount_ (DEFAULT_ROTA)
{
  model_ = model;
  graphics_ids_ = new std::vector<GraphicsInstance>();
  add_graphics_item(shaderId);
  build_matrix();
}

ModelInstance::~ModelInstance() {
  delete graphics_ids_;
}

void ModelInstance::setPosition(vec3 newPos) {
  pos_ = newPos;
  build_matrix();
}

void ModelInstance::setScale(vec3 newScale) {
  scale_ = newScale;
  build_matrix();
}

void ModelInstance::setRotation(vec3 rotAxis, float rotAmount) {
  rot_ = rotAxis;
  rot_amount_ = rotAmount;
  build_matrix();
}

Model *ModelInstance::get_model() {
  return model_;
}

const std::vector<GraphicsInstance> *ModelInstance::get_graphics_ids() {
  return graphics_ids_;
}

void ModelInstance::build_matrix() {
  matrix_ = rotate(scale(translate(mat4(1.0f), pos_), scale_), rot_amount_, rot_);
}

const glm::mat4 ModelInstance::getModelMatrix() const {
  return matrix_;
}

void ModelInstance::add_graphics_item(int graphics_item_id) {
  GraphicsInstance newItem = {graphics_item_id, true};
  graphics_ids_->push_back(newItem);
}

void ModelInstance::enable_graphics_item(int graphics_item_id) {
  for (auto graphics_item : *graphics_ids_) {
    if (graphics_item.item_id == graphics_item_id)
      graphics_item.enabled = true;
  }
}

void ModelInstance::disable_graphics_item(int graphics_item_id) {
  for (auto graphics_item : *graphics_ids_) {
    if (graphics_item.item_id == graphics_item_id)
      graphics_item.enabled = false;
  }
}
