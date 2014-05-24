#ifndef _FRAME_BUFFER_BINDER_HPP_
#define _FRAME_BUFFER_BINDER_HPP_

#include "GL/glew.h"
#include "GL/gl.h"
#include "GraphicsPipelineItem.hpp"

class FramebufferBinder : public GraphicsPipelineItem {
 public:
  FramebufferBinder(int w, int h);
  FramebufferBinder(int w, int h, bool storeColor, bool storeDepth);

  GLuint get_color_texture();
  GLuint get_depth_texture();

  void act(ModelInstance **model_instances, int num_instances) override;
 private:
  int w_, h_;
  bool store_color_;
  bool store_depth_;

  GLuint frame_buffer_;
  GLuint rendered_texture_, depth_texture_;
  bool buffer_shared_;
  GLuint depth_buffer_;
  GLenum draw_buffers_[2];
};

#endif  // _FRAME_BUFFER_BINDER_HPP_