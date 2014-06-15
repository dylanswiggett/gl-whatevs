#ifndef SHADOW_MAPPER_HPP_
#define SHADOW_MAPPER_HPP_

#include "GraphicsPipelineItem.hpp"
#include "Camera.hpp"

class ShadowMapper : public GraphicsPipelineItem {
  virtual ShadowMapper(Camera viewpoint);
  virtual ~ShadowMapper() {}

  virtual void act(ModelInstance **model_instances, int num_instances);
};

#endif  // SHADOW_MAPPER_HPP_