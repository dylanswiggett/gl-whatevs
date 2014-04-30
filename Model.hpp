#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "GL/glew.h"
#include "GL/gl.h"

class Model {
 public:
  Model(GLfloat *vertex_buffer_data, int num_vertices);
  ~Model();
 private:
  float *vertex_buffer_data_;
  int num_vertices_;
  GLuint vertex_array_id_;
};

#endif  // _MODEL_HPP_