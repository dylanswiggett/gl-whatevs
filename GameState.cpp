#include "GameState.hpp"
#include <map>
#include <string>
#include "glm/glm.hpp"

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

int GameState::add_model_instance(std::string name, ModelInstance *newInstance) {
  model_instances_->insert(std::pair<int,ModelInstance *>(id_incr_, newInstance));
  model_instance_ids_->insert(std::pair<std::string,int>(name, id_incr_));
  id_incr_++;
  return id_incr_ - 1;
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
  // TODO: Group drawing instances by shader, to improve performance.
  // TODO: Support multiple shaders on each model.

  // Draw every modelInstance individually
  std::map<int,ModelInstance *>::iterator it;
  for (it = model_instances_->begin(); it != model_instances_->end(); ++it) {
    gl_handler_->get_shader(it->second->get_shader_id())->draw(
               gl_handler_->get_model(it->second->get_model_id()),
               it->second,
               current_camera_);
  }
}