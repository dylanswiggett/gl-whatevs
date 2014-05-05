#include "GLHandler.hpp"
#include <map>
#include <string>
#include "GL/glew.h"
#include "GL/gl.h"

#define CLEAR_FLAGS GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT

using namespace std;

GLHandler::GLHandler(int width, int height) :
  width_(width), height_(height)
{
  glClearColor(1, 0, 0, 1);
  models_ = new map<int,Model *>();
  model_ids_ = new map<string,int>();
  id_incr = 1;
}

GLHandler::~GLHandler() {
  std::map<int,Model *>::iterator it;
  for (it = models_->begin(); it != models_->end(); ++it) {
    delete it->second;
  }
  delete models_;
  delete model_ids_;
}

int GLHandler::add_model(std::string name, Model *model) {
  model_ids_->insert(pair<string,int>(name, id_incr));
  models_->insert(pair<int,Model *>(id_incr, model));
  id_incr++;
  return id_incr - 1;
}

int GLHandler::get_model_id(std::string name) {
  return model_ids_->find(name)->second;
}

void GLHandler::draw_model(int id) {
  Model *model = models_->find(id)->second;
  model->draw();
}

void GLHandler::draw_model(string name) {
  draw_model(get_model_id(name));
}

void GLHandler::clear_screen() {
  glClear(CLEAR_FLAGS);
}

void GLHandler::update_screen() {
}