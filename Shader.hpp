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

// A stage in a graphics pipeline in which a GLSL shader is run.
// A shader using this class should accept matrices with the names
// defined above by SHADER_MODEL_MATRIX_NAME, SHADER_CAMERA_MATRIX_NAME
// and SHADER_PROJECTION_MATRIX_NAME to determine the necessary
// render transformations.
class Shader : public GraphicsPipelineItem {
 public:
  // Create a new shader that loads its GLSL code from the given vertexPath
  // and fragPath. The shader will be passed the view matrix representing
  // the given camera's position at each render pass.
  Shader(std::string vertexPath, std::string fragPath, const Camera * const activeCamera);
  virtual ~Shader();

  // Set uniform parameters to the shader.
  void addInputParami(std::string paramName, int param);
  void addInputParamf(std::string paramName, float param);

  // Set a texture in the shader. The texture with the given ID will be attached
  // to a uniform sampler with the given name in GLSL.
  void setTexture0(GLuint texture0, std::string name) { texture0_ = texture0; texture0_name = name; }
  void setTexture1(GLuint texture1, std::string name) { texture1_ = texture1; texture1_name = name; }

  // Run this shader on each of the given model_instances.
  virtual void act(ModelInstance **model_instances, int num_instances) override;
 protected:
  // Get the program id.
  double p_id() { return program_id_; };
  // Sets all of the opengl parameters necessary for running the shader
  // (e.g. defines uniforms, prepares textures).
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