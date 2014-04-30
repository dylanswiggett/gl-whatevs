#include "Model.hpp"
#include "GL/glew.h"
#include "GL/gl.h"

Model::Model(GLfloat *vertex_buffer_data, int num_vertices) :
  vertex_buffer_data_(vertex_buffer_data),
  num_vertices_(num_vertices)
{
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);
}

Model::~Model() {
  
}