#ifndef _GAME_LOOP_HPP_
#define _GAME_LOOP_HPP_

#include "SDL/SDL.h"
#include "GLHandler.hpp"

class GameLoop {
 public:
  GameLoop(SDL_Surface *surface);
  ~GameLoop();

  int run_game_loop();
 private:
  void hacky_setup();
  bool game_running_;
  GLHandler *gl_handler_;
};

#endif  // _GAME_LOOP_HPP_