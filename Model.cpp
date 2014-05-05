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
}

const int Model::get_vertex_buffer_id() const {
  return vertex_buffer_;
}

const int Model::get_num_vertices() const {
  return num_vertices_;
}