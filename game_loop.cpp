#include "game_loop.hpp"
#include "SDL/SDL.h"

int GameLoop::run_game_loop() {
  SDL_Event event;

  while (game_running_) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          game_running_ = false;
      }
    }


  }
  return 0;
}