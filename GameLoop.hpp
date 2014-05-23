#ifndef _GAME_LOOP_HPP_
#define _GAME_LOOP_HPP_

#include "SDL2/SDL.h"
#include "GLHandler.hpp"
#include "GraphicsPipeline.hpp"

class GameLoop {
 public:
  GameLoop(SDL_Window *window);
  ~GameLoop();

  int run_game_loop();
 private:
  void hacky_setup();
  bool game_running_;
  GLHandler *gl_handler_;
  SDL_Window *window_;
  GraphicsPipeline *game_state_;
};

#endif  // _GAME_LOOP_HPP_