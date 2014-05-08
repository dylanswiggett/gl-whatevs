#include "FrameBufferShader.hpp"
#include "Shader.hpp"
#include "GL/glew.h"
#include "GL/gl.h"

GLuint fbs_frame_buffer_id_ = 0;

FrameBufferShader::FrameBufferShader(std::string vertexPath, std::string fragPath, double priority, int width, int height) :
  Shader(vertexPath, fragPath, priority),
  w_(width),
  h_(height)
{
  frame_buffer_ = fbs_frame_buffer_id_++;
  glGenBuffers(1, &frame_buffer_);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);

  // Create the texture
  glGenTextures(1, &rendered_texture_);
  glBindTexture(GL_TEXTURE_2D, rendered_texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w_, h_, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
  
  glGenRenderbuffers(1, &depth_buffer_);
  glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w_, h_);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_); 
}

FrameBufferShader::~FrameBufferShader() {
  glDeleteBuffers(1, &frame_buffer_);
  glDeleteTextures(1, &rendered_texture_);
  glDeleteRenderbuffers(1, &depth_buffer_);
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

  glUseProgram(0);
}