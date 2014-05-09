#include "GameState.hpp"
#include "ModelInstance.hpp"
#include <map>
#include <string>
#include "glm/glm.hpp"
#include "Shader.hpp"
#include "FrameBufferShader.hpp"

GameState::GameState(GLHandler *gl_handler) {
  model_instances_ = new std::map<int,ModelInstance *>();
  model_instance_ids_ = new std::map<std::string,int>();
  // current_camera_ = new Camera(90, .01, 100,
  //   ((double) gl_handler->get_width()) / gl_handler->get_height());
  current_camera_ = cameraTowards(
    glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    90, .01, 100,
    ((double) gl_handler->get_width()) / ((double) gl_handler->get_height()));

  gl_handler_ = gl_handler;

  id_incr_ = 1;
}

GameState::~GameState() {
  std::map<int,ModelInstance *>::iterator it;
  for (it = model_instances_->begin(); it != model_instances_->end(); ++it) {
    delete it->second;
  }

  delete model_instance_ids_;

  delete model_instances_;
  delete current_camera_;
}

void GameState::set_camera(Camera *newCamera) {
  current_camera_ = newCamera;
}

ShaderGroup *GameState::get_shader_instance(int id) {
  Shader *shader = gl_handler_->get_shader(id);
  int pos = 0;

  if (draw_order_.size() > 0) {
    while (pos < (int) draw_order_.size() &&
           shader->getPriority() > draw_order_[pos].shader->getPriority())
      pos++;

    if (pos < (int) draw_order_.size() && draw_order_[pos].shader_id == id)
      return &(draw_order_[pos]);
  }

  // New shader
  ShaderGroup newInstance;
  newInstance.shader = shader;
  newInstance.shader_id = id;
  newInstance.shader_enabled = true;
  draw_order_.insert(draw_order_.begin() + pos, newInstance);

  return &(draw_order_[pos]);
}

int GameState::add_model_instance(std::string name, ModelInstance *newInstance) {
  int new_id = id_incr_++;
  model_instances_->insert(std::pair<int,ModelInstance *>(new_id, newInstance));
  model_instance_ids_->insert(std::pair<std::string,int>(name, new_id));

  for (auto shader_instance : *(newInstance->get_shader_ids())) {
    ShaderGroup *group = get_shader_instance(shader_instance.shader_id);
    group->shaded_instances.push_back(newInstance);
  }

  return new_id;
}

ModelInstance *GameState::get_model_instance(int id) {
  return model_instances_->find(id)->second;
}

int GameState::get_model_instance_id(std::string name) {
  return model_instance_ids_->find(name)->second;
}

void GameState::step() {
  // TODO: Use me!
}

void GameState::draw() {
  for (auto shader_group : draw_order_) {
    if (shader_group.shader_enabled)
      shader_group.shader->draw(&(shader_group.shaded_instances[0]), 
                                shader_group.shaded_instances.size(), current_camera_);
  }
}