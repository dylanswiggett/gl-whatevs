#ifndef _GAME_LOOP_HPP_
#define _GAME_LOOP_HPP_

#include "SDL/SDL.h"

class GameLoop {
 public:
  GameLoop(SDL_Surface *surface) : surface_(surface) {}

  int run_game_loop();
 private:
  bool game_running_;
  SDL_Surface *surface_;
};

#endif  // _GAME_LOOP_HPP_