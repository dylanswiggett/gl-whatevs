#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "GL/glew.h"
#include "GL/gl.h"
#include <string>
#include "glm/glm.hpp"

typedef struct {
  glm::vec3 pos, norm;
  glm::vec2 tex;
} Vertex;

class Model {
 public:
  Model(const GLfloat *vertex_buffer_data, const int num_vertices);
  Model(std::string filepath);
  ~Model();

  const int get_vertex_buffer_id() const;
  const int get_num_vertices() const;
 private:
  uint get_vertex_id(const Vertex &v);

  const GLfloat * const vertex_buffer_data_;
  int num_vertices_;
  GLuint vertex_array_id_, vertex_buffer_;
};

#endif  // _MODEL_HPP_