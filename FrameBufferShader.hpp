#ifndef _FRAME_BUFFER_SHADER_HPP_
#define _FRAME_BUFFER_SHADER_HPP_

#include <string>
#include "GL/glew.h"
#include "GL/gl.h"
#include "Shader.hpp"

class FrameBufferShader : public Shader {
 public:
  FrameBufferShader(std::string vertexPath, std::string fragPath, double priority, int width, int height);
  FrameBufferShader(std::string vertexPath, std::string fragPath,
    double priority, const FrameBufferShader &sharedBuffer);

  ~FrameBufferShader();

  GLuint get_rendered_texture() { return rendered_texture_; };

  void draw(ModelInstance **model_instances, int num_instances, const Camera *camera) override;

 private:
  void setup_fb();

  GLuint frame_buffer_;
  GLuint rendered_texture_;
  bool buffer_shared_;
  GLuint depth_buffer_;
  GLenum draw_buffers_[1];
  int w_, h_;
};

#endif  // _FRAME_BUFFER_SHADER_HPP_