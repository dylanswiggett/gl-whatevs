#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "GL/glew.h"
#include "GL/gl.h"
#include <string>
#include <map>
#include <vector>
#include "glm/glm.hpp"

class Vertex {
 public:
  // We need this for maps when building our VBO.
  bool operator<(const Vertex &v) const {
    if      (pos.x != v.pos.x)
      return pos.x <  v.pos.x;
    else if (pos.y != v.pos.y)
      return pos.y <  v.pos.y;
    else if (pos.z != v.pos.z)
      return pos.z <  v.pos.z;

    else if (norm.x != v.norm.x)
      return norm.x <  v.norm.x;
    else if (norm.y != v.norm.y)
      return norm.y <  v.norm.y;
    else if (norm.z != v.norm.z)
      return norm.z <  v.norm.z;

    else if (tex.x != v.tex.x)
      return tex.x <  v.tex.x;
    else
      return tex.y < v.tex.y;
  }

  glm::vec3 pos, norm;
  glm::vec2 tex;
};

typedef struct {
  unsigned int v1, v2, v3;
} Polygon;

class Model {
 public:
  // Loads the model's data from an OBJ file at the given path.
  Model(std::string filepath);
  ~Model();

  const GLuint get_element_buffer_id() const;
  void bind_gl_data() const;
  void unbind_gl_data() const;
  const unsigned int get_num_vertices() const;
 private:
  uint get_vertex_id(const Vertex &v);
  void build_vbo();

  std::map<Vertex,int> *vertices_;
  std::vector<Polygon> *faces_;

  GLuint vertex_buffer_;
  GLuint normal_buffer_;
  GLuint texcoord_buffer_;
  
  int max_vbo_id_;
  GLuint element_buffer_id_;
};

#endif  // _MODEL_HPP_