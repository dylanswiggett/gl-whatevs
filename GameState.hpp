#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <map>
#include "GLHandler.hpp"

class GameState {
 public:
  GameState(GLHandler *gl_handler);
  ~GameState();

  void set_camera(Camera *newCamera);
  int add_model_instance(ModelInstance *newInstance);

  ModelInstance *get_model_instance(int id);

  void step();
  void draw();
 private:
  map<int,ModelInstance *> *model_instances_;
  Camera *current_camera_;
  GLHandler *gl_handler_;
  int id_incr_;
};

#endif // _GAME_STATE_HPP_