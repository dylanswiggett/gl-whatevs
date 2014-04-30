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
}

GLHandler::~GLHandler() {
  /* TODO: delete all models */
}

void GLHandler::add_model(std::string name, Model *model) {
  models_.insert(pair<string,Model *>(name, model));
}

void GLHandler::update_screen() {
  glClear(CLEAR_FLAGS);
}