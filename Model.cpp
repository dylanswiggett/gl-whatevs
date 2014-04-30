#include "Model.hpp"
#include "GL/glew.h"
#include "GL/gl.h"
#include <iostream>

Model::Model(const GLfloat *vertex_buffer_data, int num_vertices) :
  vertex_buffer_data_(vertex_buffer_data),
  num_vertices_(num_vertices)
{
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);
}

Model::~Model() {
  /* TODO: Free vertex information, and remove from OpenGL */
  delete vertex_buffer_data_;
}