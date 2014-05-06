#include "Model.hpp"
#include "GL/glew.h"
#include "GL/gl.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define MAX_FILE_LINE_LENGTH 1024

using namespace std;

Model::Model(const GLfloat *vertex_buffer_data, int num_vertices) :
  vertex_buffer_data_(vertex_buffer_data),
  num_vertices_(num_vertices)
{
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);
  glGenBuffers(1, &vertex_buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * num_vertices * 3,
               vertex_buffer_data_, GL_STATIC_DRAW);
}

Model::Model(std::string filepath) {
  fstream f;
  char line[MAX_FILE_LINE_LENGTH];
  string buf;

  f.open(filepath, fstream::in);
  if (f.fail())
    throw "File not found: " + filepath;

  while (!f.fail()) {
    f.getline(line, MAX_FILE_LINE_LENGTH);

    // Thanks, stackoverflow...
    // Splits the line around spaces.
    vector<string> terms;
    stringstream stream(line);
    while (stream >> buf)
      terms.push_back(buf);
  }

  f.close();
}

Model::~Model() {
  glDeleteVertexArrays(1, &vertex_array_id_);
  delete vertex_buffer_data_;
}

const int Model::get_vertex_buffer_id() const {
  return vertex_buffer_;
}

const int Model::get_num_vertices() const {
  return num_vertices_;
}