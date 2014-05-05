#include "GameLoop.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "shader_loader.hpp"

GameLoop::GameLoop(SDL_Window *window) :
  game_running_(true), window_(window)
{
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  gl_handler_ = new GLHandler(w, h);
  game_state_ = new GameState(gl_handler_);
}

GameLoop::~GameLoop() {
  delete game_state_;
  delete gl_handler_;
}

// void GameLoop::hacky_setup() {
//   GLfloat *vertices = new GLfloat[9];

//   vertices[0] = -1.0f; vertices[1] = -1.0f; vertices[2] = 0.0f;
//   vertices[3] =  1.0f; vertices[4] = -1.0f; vertices[5] = 0.0f;
//   vertices[6] =  0.0f; vertices[7] =  1.0f; vertices[8] = 0.0f;

//   Model *triangleModel = new Model(vertices, 3);
//   triangleModel->set_program(LoadShaders(
//     "shaders/shader.vert", "shaders/shader.frag"));

//   gl_handler_->add_model("triangle", triangleModel);
// }

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

    game_state_->step();

    gl_handler_->clear_screen();

    game_state_->draw();

    SDL_GL_SwapWindow(window_);
  }
  return 0;
}
