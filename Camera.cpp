#include "Camera.hpp"

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Camera::Camera(double FOV, double nearPlane, double farPlane, double aspectRatio) : 
  pos_(vec3(0, 0, 0)),
  dir_(vec3(0, 0, 1)),
  up_(vec3(0, 1, 0)),
  FOV_(FOV),
  near_(nearPlane),
  far_(farPlane),
  ratio_(aspectRatio)
{
  build_mat();
}

Camera::Camera(vec3 pos, vec3 dir, vec3 up,
               double FOV, double nearPlane, double farPlane,
               double aspectRatio) :
  pos_(pos), dir_(dir), up_(up),
  FOV_(FOV),
  near_(nearPlane),
  far_(farPlane),
  ratio_(aspectRatio)
{
  build_mat();
}

void Camera::build_mat() {
  camera_mat_ = lookAt(pos_, dir_ + pos_, up_);
  projection_mat_ = perspective(FOV_, ratio_, near_, far_);
}

const mat4 Camera::getCamMatrix() const {
  return camera_mat_;
}

const mat4 Camera::getProjMatrix() const {
  return projection_mat_;
}

Camera *cameraTowards(vec3 pos, vec3 towards, vec3 up, double FOV,
                      double nearPlane, double farPlane, double aspectRatio) {
  return new Camera(pos, towards - pos, up, FOV, nearPlane, farPlane, aspectRatio);
}