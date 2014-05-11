#ifndef _MODEL_INSTANCE_HPP_
#define _MODEL_INSTANCE_HPP_

#include "glm/glm.hpp"
#include <string>
#include <vector>
#include "Model.hpp"

typedef struct {
  int item_id;
  bool enabled;
} GraphicsInstance;

class ModelInstance {
 public:
  ModelInstance(Model *model);
  ModelInstance(Model *model, int shaderId);
  ~ModelInstance();

  void setPosition(glm::vec3 newPos);
  void setScale(glm::vec3 newScale);
  void setRotation(glm::vec3 rotAxis, float rotAmount);

  Model *get_model();
  const std::vector<GraphicsInstance> *get_graphics_ids();

  void add_graphics_item(int item_id);
  void enable_graphics_item(int item_id);
  void disable_graphics_item(int item_id);

  const glm::mat4 getModelMatrix() const;
 private:
  void build_matrix();

  glm::vec3 pos_, scale_, rot_;
  float rot_amount_;
  glm::mat4 matrix_;
  Model *model_;
  std::vector<GraphicsInstance> *graphics_ids_;
};

#endif  // _MODEL_INSTANCE_HPP_