#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "GL/glew.h"
#include "GL/gl.h"
#include <string>

class Model {
 public:
  Model(const GLfloat *vertex_buffer_data, const int num_vertices);
  Model(std::string filepath);
  ~Model();

  const int get_vertex_buffer_id() const;
  const int get_num_vertices() const;
 private:
  const GLfloat * const vertex_buffer_data_;
  int num_vertices_;
  GLuint vertex_array_id_, vertex_buffer_;
};

#endif  // _MODEL_HPP_