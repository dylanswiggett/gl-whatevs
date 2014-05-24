#ifndef _GRAPHICS_PIPELINE_ITEM_HPP_
#define _GRAPHICS_PIPELINE_ITEM_HPP_

#include "ModelInstance.hpp"

class GraphicsPipelineItem {
 public:
  virtual ~GraphicsPipelineItem() {}

  virtual void act(ModelInstance **model_instances, int num_instances) = 0;
};

#endif  // _GRAPHICS_PIPELINE_ITEM_HPP_