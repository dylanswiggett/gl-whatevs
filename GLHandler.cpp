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
  glClearColor(0, 0, .2f, 1);
  models_ = new map<int,Model *>();
  model_ids_ = new map<string,int>();
  graphics_items_ = new map<int,GraphicsPipelineItem *>();
  graphics_item_ids_ = new map<string,int>();
  id_incr_ = 1;

  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glDepthFunc(GL_LESS);
  
}

GLHandler::~GLHandler() {
  std::map<int,Model *>::iterator modelIt;
  for (modelIt = models_->begin(); modelIt != models_->end(); ++modelIt) {
    delete modelIt->second;
  }
  delete models_;
  delete model_ids_;

  std::map<int,GraphicsPipelineItem *>::iterator graphicsIt;
  for (graphicsIt = graphics_items_->begin(); graphicsIt != shaders_->end(); ++graphicsIt) {
    delete graphicsIt->second;
  }
  delete graphics_items_;
  delete graphics_item_ids_;
}

int GLHandler::add_model(const std::string name, Model *model) {
  model_ids_->insert(pair<string,int>(name, id_incr_));
  models_->insert(pair<int,Model *>(id_incr_, model));
  id_incr_++;
  return id_incr_ - 1;
}

int GLHandler::get_model_id(const std::string name) const {
  return model_ids_->find(name)->second;
}

Model *GLHandler::get_model(const std::string name) const {
  return get_model(get_model_id(name));
}

Model *GLHandler::get_model(const int id) const {
  return models_->find(id)->second;
}

int GLHandler::add_graphics_item(const std::string name, GraphicsPipelineItem *graphics_item) {
  graphics_item_ids_->insert(pair<string,int>(name, id_incr_));
  graphics_items_->insert(pair<int,GraphicsPipelineItem *>(id_incr_, graphics_item));
  id_incr_++;
  return id_incr_ - 1;
}

int GLHandler::get_graphics_item_id(const std::string name) const {
  return graphics_item_ids_->find(name)->second;
}

Shader *GLHandler::get_graphics_item(const int id) const {
  return graphics_items_->find(id)->second;
}

void GLHandler::clear_screen() {
  glClear(CLEAR_FLAGS);
}

void GLHandler::update_screen() {
}

int GLHandler::get_width() const {
  return width_;
}

int GLHandler::get_height() const {
  return height_;
}
