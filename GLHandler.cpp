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
  models_ = new map<string,Model *>();
}

GLHandler::~GLHandler() {
  std::map<string,Model *>::iterator it;
  for (it = models_->begin(); it != models_->end(); ++it) {
    delete it->second;
  }
  delete models_;
}

void GLHandler::add_model(std::string name, Model *model) {
  models_->insert(pair<string,Model *>(name, model));
}

void GLHandler::draw_model(std::string name) {
  Model *model = models_->find(name)->second;
  model->draw();
}

void GLHandler::clear_screen() {
  glClear(CLEAR_FLAGS);
}

void GLHandler::update_screen() {
}