#ifndef _FRAME_BUFFER_SHADER_HPP_
#define _FRAME_BUFFER_SHADER_HPP_

#include <string>

class FrameBufferShader : Shader {
  FrameBufferShader(std::string vertexPath, std::string fragPath, double priority);
  FrameBufferShader(std::string vertexPath, std::string fragPath, double priority, FrameBufferShader sharedBuffer);

  GLuint get_rendered_texture() { return rendered_texture_ };

 private:
  GLuint frame_buffer_;
  GLuint rendered_texture_;
};

#endif  // _FRAME_BUFFER_SHADER_HPP_