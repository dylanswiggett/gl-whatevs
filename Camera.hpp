#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "glm/glm.hpp"

// Represents a single point of view in three-dimensional space.
// Easly convertible to OpenGL matrices.
class Camera {
 public:
  // Construct a camera with the given view parameters, but facing in
  // a default direction from the origin.
  Camera(double FOV, double nearPlane, double farPlane, double aspectRatio);
  // Construct a camera with the given view parameters, and the given
  // three direction vectors. These vectors must be orthonormal.
  Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, double FOV,
         double nearPlane, double farPlane, double aspectRatio);

  // Get the view matrix for use in OpenGL.
  const glm::mat4 getCamMatrix() const;
  // Get the projection matrix for use in OpenGL.
  const glm::mat4 getProjMatrix() const;
 private:
  void build_mat();

  glm::vec3 pos_, dir_, up_;
  glm::mat4 camera_mat_, projection_mat_;
  double FOV_, near_, far_, ratio_;
};

#endif  // _CAMERA_HPP_

// Create a new camera looking from the given position towards
// the given point.
Camera *cameraTowards(glm::vec3 pos, glm::vec3 towards, glm::vec3 up,
  double FOV, double nearPlane, double farPlane, double aspectRatio);