#ifndef _SHADER_HPP_
#define _SHADER_HPP_

class Shader {
 public:
  void draw(const ModelInstance *model, const Camera *camera);
 private:
  GLuint program_id_;
};

#endif  // _SHADER_HPP_