#include "Shader.hpp"
#include "glm/glm.hpp"

#include "ModelInstance.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "shader_loader.hpp"
#include <string>
#include "GL/gl.h"
#include <vector>
#include <iostream>

Shader::Shader(std::string vertexPath, std::string fragPath, double priority) :
  priority_(priority),
  texture0_(0), texture1_(0)
{
  program_id_ = LoadShaders(vertexPath.c_str(), fragPath.c_str());
  int_parameters_ = new std::vector<shader_intParam>;
  float_parameters_ = new std::vector<shader_floatParam>;
}

Shader::~Shader() {
  glDeleteProgram(program_id_);
}

void Shader::addInputParami(std::string paramName, int param) {
  shader_intParam newParam {paramName, param};
  int_parameters_->push_back(newParam);
}

void Shader::addInputParamf(std::string paramName, float param) {
  shader_floatParam newParam {paramName, param};
  float_parameters_->push_back(newParam);
}

void Shader::set_params() {
  for (auto int_param : *int_parameters_) {
    GLuint loc = glGetUniformLocation(program_id_, int_param.name.c_str());
    glUniform1i(loc, int_param.value);
  }

  for (auto float_param : *float_parameters_) {
    GLfloat loc = glGetUniformLocation(program_id_, float_param.name.c_str());
    glUniform1f(loc, float_param.value);
  }

  if (texture0_) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0_);
    GLfloat loc = glGetUniformLocation(program_id_, texture0_name.c_str());
    glUniform1f(loc, 0);
  }

  if (texture1_) {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1_);
    GLfloat loc = glGetUniformLocation(program_id_, texture1_name.c_str());
    glUniform1f(loc, 1);
  }
}

void Shader::draw(ModelInstance **model_instances, int num_instances, const Camera *camera) {
  glUseProgram(program_id_);
  set_params();

  GLuint modelMatId = glGetUniformLocation(program_id_, SHADER_MODEL_MATRIX_NAME);
  GLuint cameraMatId = glGetUniformLocation(program_id_, SHADER_CAMERA_MATRIX_NAME);
  GLuint projectionMatId = glGetUniformLocation(program_id_, SHADER_PROJECTION_MATRIX_NAME);

  glUniformMatrix4fv(cameraMatId, 1, GL_FALSE, &(camera->getCamMatrix())[0][0]);
  glUniformMatrix4fv(projectionMatId, 1, GL_FALSE, &(camera->getProjMatrix())[0][0]);

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

double Shader::getPriority() {
  return priority_;
}