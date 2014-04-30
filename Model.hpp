#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "GL/glew.h"
#include "GL/gl.h"

class Model {
 public:
  Model(const GLfloat *vertex_buffer_data, int num_vertices);
  ~Model();

  void draw();
 private:
  const GLfloat * const vertex_buffer_data_;
  int num_vertices_;
  GLuint vertex_array_id_, vertex_buffer_;
};

#endif  // _MODEL_HPP_