#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "GL/glm.h"

class Camera {
 public:
  glm::mat4 getMatrix();
 private:
  glm::vec3 pos, dir;
  double FOV;
};

#endif  // _CAMERA_HPP_