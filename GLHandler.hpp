#ifndef _GL_HANDLER_HPP_
#define _GL_HANDLER_HPP_

#include "Model.hpp"
#include "Shader.hpp"
#include <map>
#include <string>

class GLHandler {
 public:
  // Constructors
  /*
   * Requires a GL context exist.
   */
  GLHandler(int width, int height);
  ~GLHandler();

  void clear_screen();
  void update_screen();
  int add_model(const std::string name, Model *model);
  int get_model_id(const std::string name) const;
  Model *get_model(const std::string name) const;
  Model *get_model(const int id) const;
  int add_shader(const std::string name, Shader *shader);
  int get_shader_id(const std::string name) const;
  Shader *get_shader(const int id) const;

  int get_width() const;
  int get_height() const;
 private:
  int id_incr_;

  GLuint vertex_array_id_;

  std::map<int,Model *> *models_;
  std::map<std::string,int> *model_ids_;

  std::map<int,Shader *> *shaders_;
  std::map<std::string,int> *shader_ids_;

  int width_, height_;
};

#endif  // _GL_HANDLER_HPP_