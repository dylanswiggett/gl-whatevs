#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include "ModelInstance.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include <string>
#include "GL/gl.h"

class Shader {
 public:
  Shader(std::string vertexPath, std::string fragPath);
  ~Shader();

  void draw(const Model *model, const ModelInstance *model_instance, const Camera *camera);
 private:
  GLuint program_id_;
};

#endif  // _SHADER_HPP_