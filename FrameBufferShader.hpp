#ifndef _FRAME_BUFFER_SHADER_HPP_
#define _FRAME_BUFFER_SHADER_HPP_

#include <string>
#include "GL/glew.h"
#include "GL/gl.h"
#include "Shader.hpp"

class FrameBufferShader : public Shader {
 public:
  FrameBufferShader(std::string vertexPath, std::string fragPath, double priority, int width, int height);

  ~FrameBufferShader();

  GLuint get_rendered_texture() { return rendered_texture_; };

  void draw(ModelInstance **model_instances, int num_instances, const Camera *camera);

 private:
  GLuint frame_buffer_;
  GLuint rendered_texture_;
  GLuint depth_buffer_;
  int w_, h_;
};

#endif  // _FRAME_BUFFER_SHADER_HPP_