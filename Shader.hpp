#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include "ModelInstance.hpp"
#include "GraphicsPipelineItem.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include <string>
#include <vector>
#include "GL/gl.h"

#define SHADER_MODEL_MATRIX_NAME "modelMat"
#define SHADER_CAMERA_MATRIX_NAME "cameraMat"
#define SHADER_PROJECTION_MATRIX_NAME "projMat"

typedef struct {
  std::string name;
  int value;
} shader_intParam;

typedef struct {
  std::string name;
  float value;
} shader_floatParam;

class Shader : public GraphicsPipelineItem {
 public:
  Shader(std::string vertexPath, std::string fragPath, const Camera * const activeCamera);
  virtual ~Shader();

  void addInputParami(std::string paramName, int param);
  void addInputParamf(std::string paramName, float param);

  void setTexture0(GLuint texture0, std::string name) { texture0_ = texture0; texture0_name = name; }
  void setTexture1(GLuint texture1, std::string name) { texture1_ = texture1; texture1_name = name; }

  virtual void act(ModelInstance **model_instances, int num_instances) override;
 protected:
  double p_id() { return program_id_; };
  void set_params();
 private:
  GLuint texture0_, texture1_;
  std::string texture0_name, texture1_name;
  std::vector<shader_intParam> *int_parameters_;
  std::vector<shader_floatParam> *float_parameters_;
  GLuint program_id_;
  const Camera * const active_camera_;
};

#endif  // _SHADER_HPP_