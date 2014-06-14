#ifndef _FRAME_BUFFER_BINDER_HPP_
#define _FRAME_BUFFER_BINDER_HPP_

#include "GL/glew.h"
#include "GL/gl.h"
#include "GraphicsPipelineItem.hpp"

// A graphics pipeline element that switches the framebuffer to
// which subsequent pipeline elements will render.
class FramebufferBinder : public GraphicsPipelineItem {
 public:
  // Create a new FramebufferBinder that sets the framebuffer to the
  // default screenbuffer.
  FramebufferBinder(int w, int h);
  // Create a new FramebufferBinder. If storeColor or storeDepth is
  // true, the color buffer and depth buffer (respectively) will be
  // stored as textures. Otherwise, these will be stored as buffers.
  FramebufferBinder(int w, int h, bool storeColor, bool storeDepth);

  // Returns the id for the color buffer texture, if one is used.
  GLuint get_color_texture();
  // Returns the id for the depth buffer texture, if one is used.
  GLuint get_depth_texture();

  // See GraphicsPipelineItem.hpp
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