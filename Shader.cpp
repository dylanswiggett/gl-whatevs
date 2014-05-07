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

Shader::Shader(std::string vertexPath, std::string fragPath) {
  program_id_ = LoadShaders(
    "shaders/shader.vert", "shaders/shader.frag");
}

Shader::~Shader() {
}

void Shader::draw(const Model *model, const ModelInstance *model_instance,
                  const Camera *camera) {
  // TODO: Update to accept a list of models rather than a single model.

  glUseProgram(program_id_);

  GLuint modelMatId = glGetUniformLocation(program_id_, MODEL_MATRIX_NAME);
  GLuint cameraMatId = glGetUniformLocation(program_id_, CAMERA_MATRIX_NAME);
  GLuint projectionMatId = glGetUniformLocation(program_id_, PROJECTION_MATRIX_NAME);

  glUniformMatrix4fv(modelMatId, 1, GL_FALSE, &(model_instance->getModelMatrix())[0][0]);
  glUniformMatrix4fv(cameraMatId, 1, GL_FALSE, &(camera->getCamMatrix())[0][0]);
  glUniformMatrix4fv(projectionMatId, 1, GL_FALSE, &(camera->getProjMatrix())[0][0]);

  model->bind_gl_data();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->get_element_buffer_id());
  glDrawElements(GL_TRIANGLES, model->get_num_vertices(), GL_UNSIGNED_INT, NULL);

  model->unbind_gl_data();

  glUseProgram(0);
}
