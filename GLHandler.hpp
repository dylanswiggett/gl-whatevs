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
  void add_model(std::string name, Model *model);
  void draw_model(std::string name);
 private:
  int width_, height_;
  std::map<std::string,Model *> *models_;
};

#endif  // _GL_HANDLER_HPP_