#include "GraphicsPipeline.hpp"
#include "ModelInstance.hpp"
#include <map>
#include <string>
#include <iostream>
#include "glm/glm.hpp"
#include "Shader.hpp"
#include "FramebufferBinder.hpp"
#include "GraphicsPipelineItem.hpp"

GraphicsPipeline::GraphicsPipeline(GLHandler *gl_handler) {
  model_instances_ = new std::map<int,ModelInstance *>();
  model_instance_ids_ = new std::map<std::string,int>();

  current_camera_ = cameraTowards(
    glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
    90, .01, 100,
    ((double) gl_handler->get_width()) / ((double) gl_handler->get_height()));

  gl_handler_ = gl_handler;

  id_incr_ = 1;
}

GraphicsPipeline::~GraphicsPipeline() {
  std::map<int,ModelInstance *>::iterator it;
  for (it = model_instances_->begin(); it != model_instances_->end(); ++it) {
    delete it->second;
  }

  delete model_instance_ids_;

  delete model_instances_;
  delete current_camera_;
}

void GraphicsPipeline::set_camera(Camera *newCamera) {
  current_camera_ = newCamera;
}

void GraphicsPipeline::add_graphics_step(std::string name, double priority) {
  get_graphics_instance(gl_handler_->get_graphics_item_id(name), priority);
}

GraphicsPipelineGroup *GraphicsPipeline::get_graphics_instance(int id, double priority, bool check_priority) {
  GraphicsPipelineItem *graphics_item = gl_handler_->get_graphics_item(id);
  int pos = 0;

  if (draw_order_.size() > 0) {
    if (check_priority) {
      while (pos < (int) draw_order_.size() &&
             priority > draw_order_[pos].priority)
        pos++;
    } else {
      while (pos < (int) draw_order_.size() &&
             draw_order_[pos].item_id != id)
        pos++;
    }

    if (pos < (int) draw_order_.size() && draw_order_[pos].item_id == id)
      return &(draw_order_[pos]);
  }

  // New shader
  GraphicsPipelineGroup newGroup;
  newGroup.item = graphics_item;
  newGroup.item_id = id;
  newGroup.enabled = true;
  newGroup.priority = priority;
  draw_order_.insert(draw_order_.begin() + pos, newGroup);

  return &(draw_order_[pos]);
}

int GraphicsPipeline::add_model_instance(std::string name, ModelInstance *newInstance) {
  int new_id = id_incr_++;
  model_instances_->insert(std::pair<int,ModelInstance *>(new_id, newInstance));
  model_instance_ids_->insert(std::pair<std::string,int>(name, new_id));

  for (auto graphics_item : *(newInstance->get_graphics_ids())) {
    GraphicsPipelineGroup *group = get_graphics_instance(graphics_item.item_id, -1, false);
    group->used_instances.push_back(newInstance);
  }

  return new_id;
}

ModelInstance *GraphicsPipeline::get_model_instance(int id) {
  return model_instances_->find(id)->second;
}

int GraphicsPipeline::get_model_instance_id(std::string name) {
  return model_instance_ids_->find(name)->second;
}

void GraphicsPipeline::step() {
  // TODO: Use me!
}

void GraphicsPipeline::draw() {
  for (auto graphics_group : draw_order_) {
    if (graphics_group.enabled)
      graphics_group.item->act(&(graphics_group.used_instances[0]), 
                                graphics_group.used_instances.size());
  }
}