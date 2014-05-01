#include "Model.hpp"
#include "GL/glew.h"
#include "GL/gl.h"
#include <iostream>

#define DEFAULT_PROGRAM_ID

Model::Model(const GLfloat *vertex_buffer_data, int num_vertices) :
  vertex_buffer_data_(vertex_buffer_data),
  num_vertices_(num_vertices),
  program_id_(nullptr)
{
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);
  glGenBuffers(1, &vertex_buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * num_vertices * 3,
               vertex_buffer_data, GL_STATIC_DRAW);
}

Model::~Model() {
  /* TODO: Free vertex information, and remove from OpenGL */
  glDeleteVertexArrays(1, &vertex_array_id_);
  delete vertex_buffer_data_;
  if (program_id_ != nullptr)
    delete program_id_;
}

void Model::draw() {
  if (program_id_ != nullptr)
    glUseProgram(*program_id_);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glVertexAttribPointer(0, num_vertices_, GL_FLOAT, GL_FALSE, 0, (void *)0);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
}

void Model::set_program(GLuint program_id) {
  if (program_id_ == nullptr)
    program_id_ = new GLuint;
  *program_id_ = program_id;
}