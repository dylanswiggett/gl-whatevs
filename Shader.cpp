#include "Shader.hpp"
#include "glm/glm.hpp"

#include "ModelInstance.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "shader_loader.hpp"
#include <string>
#include "GL/gl.h"
#include <iostream>

#define MODEL_MATRIX_NAME "modelMat"
#define CAMERA_MATRIX_NAME "cameraMat"
#define PROJECTION_MATRIX_NAME "projMat"

Shader::Shader(std::string vertexPath, std::string fragPath, double priority) :
  priority_(priority)
{
  program_id_ = LoadShaders(vertexPath.c_str(), fragPath.c_str());
}

Shader::~Shader() {
  glDeleteProgram(program_id_);
}

void Shader::draw(ModelInstance **model_instances, int num_instances, const Camera *camera) {
  // TODO: Update to accept a list of models rather than a single model.

  glUseProgram(program_id_);

  GLuint modelMatId = glGetUniformLocation(program_id_, MODEL_MATRIX_NAME);
  GLuint cameraMatId = glGetUniformLocation(program_id_, CAMERA_MATRIX_NAME);
  GLuint projectionMatId = glGetUniformLocation(program_id_, PROJECTION_MATRIX_NAME);

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