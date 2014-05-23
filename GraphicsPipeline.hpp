#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <map>
#include <string>
#include <vector>
#include "GLHandler.hpp"
#include "Camera.hpp"
#include "ModelInstance.hpp"
#include "GraphicsPipelineItem.hpp"

typedef struct {
  GraphicsPipelineItem *item;
  int item_id;
  bool enabled;
  double priority;
  std::vector<ModelInstance *> used_instances;
} GraphicsPipelineGroup;

class GraphicsPipeline {
 public:
  GraphicsPipeline(GLHandler *gl_handler);

  // Note: This does NOT free gl_handler_. The client must do this.
  ~GraphicsPipeline();

  void set_camera(Camera *newCamera);
  int add_model_instance(std::string name, ModelInstance *newInstance);

  // TODO: make the get methods throw exceptions at unfound items.
  ModelInstance *get_model_instance(int id);
  int get_model_instance_id(std::string name);

  void add_graphics_step(std::string name, double priority);

  const Camera * const get_camera() const { return current_camera_; }

  void step();
  void draw();
 private:
  GraphicsPipelineGroup *get_graphics_instance(int id, double priority, bool check_priority=true);

  std::vector<GraphicsPipelineGroup> draw_order_;
  std::map<std::string,int> *model_instance_ids_;
  std::map<int,ModelInstance *> *model_instances_;
  Camera *current_camera_;
  GLHandler *gl_handler_;
  int id_incr_;
};

#endif // _GAME_STATE_HPP_