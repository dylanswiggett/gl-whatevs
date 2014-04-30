#include "Model.hpp"
#include "GL/glew.h"
#include "GL/gl.h"
#include <iostream>

Model::Model(const GLfloat *vertex_buffer_data, int num_vertices) :
  vertex_buffer_data_(vertex_buffer_data),
  num_vertices_(num_vertices)
{
  std::cout << "Here," << std::endl;
  glGenVertexArrays(1, &vertex_array_id_);
  std::cout << "There," << std::endl;
  glBindVertexArray(vertex_array_id_);
  std::cout << "And everywhere." << std::endl;
}

Model::~Model() {
  /* TODO: Free vertex information, and remove from OpenGL */
}