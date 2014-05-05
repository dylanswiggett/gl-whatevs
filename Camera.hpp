#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "glm/glm.hpp"

class Camera {
 public:
  Camera(double FOV, double nearPlane, double farPlane, double aspectRatio);
  Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, double FOV,
         double nearPlane, double farPlane, double aspectRatio);

  glm::mat4 getCamMatrix();
  glm::mat4 getProjMatrix();
 private:
  void build_mat();

  glm::vec3 pos_, dir_, up_;
  glm::mat4 camera_mat_, projection_mat_;
  double FOV_, near_, far_, ratio_;
};

#endif  // _CAMERA_HPP_

Camera *cameraTowards(glm::vec3 pos, glm::vec3 towards, glm::vec3 up,
  double FOV, double nearPlane, double farPlane, double aspectRatio);