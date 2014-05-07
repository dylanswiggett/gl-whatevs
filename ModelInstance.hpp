#ifndef _MODEL_INSTANCE_HPP_
#define _MODEL_INSTANCE_HPP_

#include "glm/glm.hpp"
#include <string>
#include <vector>
#include "Model.hpp"

typedef struct {
  int shader_id;
  bool enabled;
} ShaderInstance;

class ModelInstance {
 public:
  ModelInstance(Model *model);
  ModelInstance(Model *model, int shaderId);
  ~ModelInstance();

  void setPosition(glm::vec3 newPos);
  void setScale(glm::vec3 newScale);
  void setRotation(glm::vec3 rotAxis, float rotAmount);

  Model *get_model();
  const std::vector<ShaderInstance> *get_shader_ids();

  void add_shader(int shader_id);
  void enable_shader(int shader_id);
  void disable_shader(int shader_id);

  const glm::mat4 getModelMatrix() const;
 private:
  void build_matrix();

  // TODO: Store a pointer to the model rather than a modelId.

  glm::vec3 pos_, scale_, rot_;
  glm::mat4 matrix_;
  float rot_amount_;
  Model *model_;
  std::vector<ShaderInstance> *shader_ids_;
};

#endif  // _MODEL_INSTANCE_HPP_