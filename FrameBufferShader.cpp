#include "FrameBufferShader.hpp"
#include "Shader.hpp"

FrameBufferShader::FrameBufferShader(std::string vertexPath, std::string fragPath, double priority) :
  Shader(vertexPath, fragPath, priority)
{
  
}

FrameBufferShader::FrameBufferShader(std::string vertexPath, std::string fragPath, double priority, FrameBufferShader sharedBuffer) :
  Shader(vertexPath, fragPath, priority)
{
  frame_buffer_ = sharedBuffer.frame_buffer_;
  rendered_texture_ = sharedBuffer.rendered_texture_;

  
}
