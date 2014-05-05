#include "ModelInstance.hpp"

ModelInstance::ModelInstance(int modelId, int shaderId) {
  model_id_ = modelId;
  shader_id_ = shaderId;
}

int ModelInstance::get_model_id() {
  return model_id_;
}

int ModelInstance::get_shader_id() {
  return shader_id_;
}
