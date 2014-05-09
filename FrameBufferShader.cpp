#include "FrameBufferShader.hpp"
#include "Shader.hpp"
#include "GL/glew.h"
#include "GL/gl.h"
#include <iostream>

GLuint fbs_frame_buffer_id_ = 1;

FrameBufferShader::FrameBufferShader(std::string vertexPath, std::string fragPath, double priority, int width, int height) :
  Shader(vertexPath, fragPath, priority),
  buffer_shared_(false),
  w_(width),
  h_(height)
{
  setup_fb();
}

FrameBufferShader::FrameBufferShader(std::string vertexPath, std::string fragPath,
                  double priority, const FrameBufferShader &sharedBuffer) :
  Shader(vertexPath, fragPath, priority),
  frame_buffer_(sharedBuffer.frame_buffer_),
  rendered_texture_(sharedBuffer.rendered_texture_),
  depth_texture_(sharedBuffer.depth_texture_),
  buffer_shared_(true),
  depth_buffer_(sharedBuffer.depth_buffer_),
  w_(sharedBuffer.w_),
  h_(sharedBuffer.h_)
{
  draw_buffers_[0] = sharedBuffer.draw_buffers_[0];
  draw_buffers_[1] = sharedBuffer.draw_buffers_[1];
}

void FrameBufferShader::setup_fb() {
  frame_buffer_ = fbs_frame_buffer_id_++;
  glGenFramebuffers(1, &frame_buffer_);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);

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
}

FrameBufferShader::~FrameBufferShader() {
  if (!buffer_shared_) {
    glDeleteBuffers(1, &frame_buffer_);
    glDeleteTextures(1, &rendered_texture_);
    glDeleteRenderbuffers(1, &depth_buffer_);
    glDeleteTextures(1, &depth_texture_);
  }
}

void FrameBufferShader::draw(ModelInstance **model_instances, int num_instances, const Camera *camera) {
  glUseProgram(Shader::p_id());

  GLuint modelMatId = glGetUniformLocation(Shader::p_id(), SHADER_MODEL_MATRIX_NAME);
  GLuint cameraMatId = glGetUniformLocation(Shader::p_id(), SHADER_CAMERA_MATRIX_NAME);
  GLuint projectionMatId = glGetUniformLocation(Shader::p_id(), SHADER_PROJECTION_MATRIX_NAME);

  glUniformMatrix4fv(cameraMatId, 1, GL_FALSE, &(camera->getCamMatrix())[0][0]);
  glUniformMatrix4fv(projectionMatId, 1, GL_FALSE, &(camera->getProjMatrix())[0][0]);

  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);
  glViewport(0, 0, w_, h_);

  Shader::set_params();

  if (!buffer_shared_)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // std::cout << "Setup fb." << std::endl;

  for (int i = 0; i < num_instances; i++) {
    ModelInstance *model_instance = model_instances[i];
    Model *model = model_instance->get_model();

    // TODO: Allow disabling shaders on models.

    glUniformMatrix4fv(modelMatId, 1, GL_FALSE, &(model_instance->getModelMatrix())[0][0]);

    model->bind_gl_data();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->get_element_buffer_id());
    glDrawElements(GL_TRIANGLES, model->get_num_vertices(), GL_UNSIGNED_INT, NULL);

    model->unbind_gl_data();
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glUseProgram(0);
}