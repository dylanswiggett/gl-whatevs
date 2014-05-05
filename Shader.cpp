#include "Shader.hpp"
#include "glm/glm.hpp"

#include "ModelInstance.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "shader_loader.hpp"
#include <string>
#include "GL/gl.h"

Shader::Shader(std::string vertexPath, std::string fragPath) {
  program_id_ = LoadShaders(
    "shaders/shader.vert", "shaders/shader.frag")
}

Shader::~Shader() {
  delete program_id_;
}

void Shader::draw(const Model *model, const ModelInstance *model_instance,
                  const Camera *camera) {
  glUseProgram(*program_id_);

  // TODO: Use camera

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, model->get_vertex_buffer_id());
  glVertexAttribPointer(0, model->get_num_vertices(), 
                        GL_FLOAT, GL_FALSE, 0, (void *)0);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);

  glUseProgram(0);
}
