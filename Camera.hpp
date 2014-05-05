#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "glm/glm.hpp"

class Camera {
 public:
  Camera();
  ~Camera();

  glm::mat4 getMatrix();
 private:
  glm::vec3 pos_, dir_;
  double FOV;
};

#endif  // _CAMERA_HPP_