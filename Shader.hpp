#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include "ModelInstance.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include <string>
#include "GL/gl.h"

#define SHADER_MODEL_MATRIX_NAME "modelMat"
#define SHADER_CAMERA_MATRIX_NAME "cameraMat"
#define SHADER_PROJECTION_MATRIX_NAME "projMat"

class Shader {
 public:
  Shader(std::string vertexPath, std::string fragPath, double priority);
  ~Shader();

  void draw(ModelInstance **model_instances, int num_instances, const Camera *camera);

  double getPriority();
 protected:
  double p_id() { return program_id_; };
 private:
  double priority_;
  GLuint program_id_;
};

#endif  // _SHADER_HPP_