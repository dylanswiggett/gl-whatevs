#ifndef _GL_HANDLER_HPP_
#define _GL_HANDLER_HPP_

#include "Model.hpp"
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
  int add_model(std::string name, Model *model);
  int get_model_id(std::string name);
  void draw_model(std::string modelName, std::string shaderName);
  void draw_model(int modelId, int shaderId);
 private:
  int id_incr_;

  std::map<int,Model *> *models_;
  std::map<std::string,int> *model_ids_;

  std::map<int,Shader *> *shaders_;
  std::map<std::string,int> *shader_ids_;

  int width_, height_;
};

#endif  // _GL_HANDLER_HPP_