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

Model::Model(std::string filepath) :
  max_vbo_id_(0)
{
  fstream f;
  char line[MAX_FILE_LINE_LENGTH];
  string buf;
  map<Vertex,int> vertex_ids;
  vector<vec3> positions, norms;
  vector<vec2> textureCoords;
  int p1, p2, p3, t1, t2, t3, n1, n2, n3;
  Vertex newVertex;
  Polygon newPolygon;

  vertices_ = new map<Vertex,int>;
  faces_ = new vector<Polygon>;

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

    if (terms.size() == 0)
      continue;

    // Process lines from an OBJ (blender) file.

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
      sscanf(terms[1].c_str(), "%i/%i/%i", &p1, &t1, &n1);
      sscanf(terms[2].c_str(), "%i/%i/%i", &p2, &t2, &n2);
      sscanf(terms[3].c_str(), "%i/%i/%i", &p3, &t3, &n3);

      newVertex.pos = positions[p1 - 1];
      newVertex.norm = norms[n1 - 1];
      if (t1 <= (int) textureCoords.size())
        newVertex.tex = textureCoords[t1 - 1];
      else
        newVertex.tex = vec2();
      newPolygon.v1 = get_vertex_id(newVertex);

      newVertex.pos = positions[p2 - 1];
      newVertex.norm = norms[n2 - 1];
      if (t2 <= (int) textureCoords.size())
        newVertex.tex = textureCoords[t2 - 1];
      else
        newVertex.tex = vec2();
      newPolygon.v2 = get_vertex_id(newVertex);

      newVertex.pos = positions[p3 - 1];
      newVertex.norm = norms[n3 - 1];
      if (t3 <= (int) textureCoords.size())
        newVertex.tex = textureCoords[t3 - 1];
      else
        newVertex.tex = vec2();
      newPolygon.v3 =  get_vertex_id(newVertex);

      faces_->push_back(newPolygon);
    }
  }

  f.close();
}

Model::~Model() {
  // TODO: Free all opengl allocations
  delete vertices_;
  delete faces_;
}

const int Model::get_vertex_buffer_id() const {
  return vertex_buffer_;
}

const int Model::get_num_vertices() const {
  return faces_->size() * 3;
}

uint Model::get_vertex_id(const Vertex &v) {
  map<Vertex,int>::iterator found = vertices_->find(v);
  if (found == vertices_->end()) {
    // Add new vertex.
    vertices_->insert(pair<Vertex,int>(v, max_vbo_id_++));
    return max_vbo_id_ - 1;
  } else {
    // Existing vertex.
    return found->second;
  }
}

void Model::build_vbo() {
  vector<unsigned int> indices;
  map<Vertex,int>::iterator it;

  // TODO: Do this for the normals and texcoords too.

  // Generate our float arrays
  float *vertex_data = new float[vertices_->size() * 3];
  for (it = vertices_->begin(); it != vertices_->end(); ++it) {
    vertex_data[it->second * 3 + 0] = it->first.pos.x;
    vertex_data[it->second * 3 + 1] = it->first.pos.y;
    vertex_data[it->second * 3 + 2] = it->first.pos.z;
  }

  // Fill indices
  for (auto poly : *faces_) {
    indices.push_back(poly.v1);
    indices.push_back(poly.v2);
    indices.push_back(poly.v3);
  }

  // Build the Buffers
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);

  glGenBuffers(1, &vertex_buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

  // Build the VBO
  glGenBuffers(1, &element_buffer_id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);

  // Free our float arrays
  delete [] vertex_data;
}