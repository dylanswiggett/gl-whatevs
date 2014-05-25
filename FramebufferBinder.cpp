#include "FramebufferBinder.hpp"
#include "GL/glew.h"
#include "GL/gl.h"
#include <iostream>

int frame_buffer_binder_id_ = 1;

FramebufferBinder::FramebufferBinder(int w, int h) :
  w_(w), h_(h),
  store_color_(false), store_depth_(false),
  frame_buffer_(0)
{
  /* ... */
}

FramebufferBinder::FramebufferBinder(int w, int h, bool storeColor, bool storeDepth) :
  w_(w), h_(h),
  store_color_(storeColor), store_depth_(storeDepth)
{
  frame_buffer_ = frame_buffer_binder_id_++;
  glGenFramebuffers(1, &frame_buffer_);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);

  // TODO: use depth buffers depending on whether storeColor or storeDepth are set to false.

  // Create the texture
  glGenTextures(1, &rendered_texture_);
  glBindTexture(GL_TEXTURE_2D, rendered_texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w_, h_, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, rendered_texture_, 0);
  
  // Create the texture
  glGenTextures(1, &depth_texture_);
  glBindTexture(GL_TEXTURE_2D, depth_texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w_, h_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture_, 0);


  draw_buffers_[0] = GL_COLOR_ATTACHMENT0;
  draw_buffers_[1] = GL_DEPTH_ATTACHMENT;
  glDrawBuffers(2, draw_buffers_);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "Failed to create frame buffer." << std::endl;
  else
    std::cout << "Created frame buffer." << std::endl;

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FramebufferBinder::get_color_texture() {
  return rendered_texture_;
}

GLuint FramebufferBinder::get_depth_texture() {
  return depth_texture_;
}

void FramebufferBinder::act(ModelInstance **model_instances, int num_instances) {
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);
  if (frame_buffer_ != 0) {
    glViewport(0, 0, w_, h_);
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}