#include "Model.hpp"
#include "GL/glew.h"
#include "GL/gl.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include "glm/glm.hpp"

#define MAX_FILE_LINE_LENGTH 1024

using namespace std;
using namespace glm;

typedef struct {
  unsigned int v1, v2, v3;
} Polygon;

Model::Model(const GLfloat *vertex_buffer_data, int num_vertices) :
  vertex_buffer_data_(vertex_buffer_data),
  num_vertices_(num_vertices)
{
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);
  glGenBuffers(1, &vertex_buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * num_vertices * 3,
               vertex_buffer_data, GL_STATIC_DRAW);
}

Model::Model(std::string filepath) :
  vertex_buffer_data_(nullptr)
{
  fstream f;
  char line[MAX_FILE_LINE_LENGTH];
  string buf;
  map<Vertex,int> vertex_ids;
  vector<vec3> positions, norms;
  vector<vec2> textureCoords;

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

    if (terms[0] == "v") {
      positions.push_back(
        vec3(strtof(terms[1].c_str(), NULL),
             strtof(terms[2].c_str(), NULL),
             strtof(terms[3].c_str(), NULL)));
    } else if (terms[0] == "vt") {
      textureCoords.push_back(
        vec2(strtof(terms[1].c_str(), NULL),
             strtof(terms[2].c_str(), NULL)));
    } else if (terms[0] == "vn") {
      norms.push_back(
        vec3(strtof(terms[1].c_str(), NULL),
             strtof(terms[2].c_str(), NULL),
             strtof(terms[3].c_str(), NULL)));
    } else if (terms[0] == "f") {
      /* TODO: actual stuff! */
    }
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