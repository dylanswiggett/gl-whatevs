#include "GameState.hpp"
#include <map>

GameState::GameState(GLHandler *gl_handler) {
  model_instances_ = new std::map<int,ModelInstance *>();
  current_camera_ = new Camera(90, .01, 100,
    ((double) gl_handler->get_width()) / gl_handler->get_height());

  gl_handler_ = gl_handler;

  id_incr_ = 1;
}

GameState::~GameState() {
  std::map<int,ModelInstance *>::iterator it;
  for (it = model_instances_->begin(); it != model_instances_->end(); ++it) {
    delete it->second;
  }

  delete model_instances_;
  delete current_camera_;
}

void GameState::set_camera(Camera *newCamera) {
  current_camera_ = newCamera;
}

int GameState::add_model_instance(ModelInstance *newInstance) {
  model_instances_->insert(std::pair<int,ModelInstance *>(id_incr_, newInstance));
  id_incr_++;
  return id_incr_ - 1;
}

ModelInstance *GameState::get_model_instance(int id) {
  return model_instances_->find(id)->second;
}

void GameState::step() {
  // TODO: Use me!
}

void GameState::draw() {
  // Draw every modelInstance individually
  std::map<int,ModelInstance *>::iterator it;
  for (it = model_instances_->begin(); it != model_instances_->end(); ++it) {
    gl_handler_->get_shader(it->second->get_shader_id())->draw(
               gl_handler_->get_model(it->second->get_model_id()),
               it->second,
               current_camera_);
  }
}