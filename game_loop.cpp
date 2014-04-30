#include "game_loop.hpp"
#include "SDL/SDL.h"

GameLoop::GameLoop(SDL_Surface *surface) :
  game_running_(true)
{
  gl_handler_ = new GLHandler(surface->w, surface->h);
}

GameLoop::~GameLoop() {
  delete gl_handler_;
}

void GameLoop::hacky_setup() {
  /* Do my testing stuff here */
}

int GameLoop::run_game_loop() {
  SDL_Event event;

  hacky_setup();

  while (game_running_) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          game_running_ = false;
      }
    }

    gl_handler_->update_screen();

    SDL_GL_SwapBuffers();
  }
  return 0;
}