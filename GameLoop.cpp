#include "GameLoop.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "shader_loader.hpp"
#include "glm/glm.hpp"

#define FPS 60

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

/*
 * TODO: Make a better setup procedure!
 */
void GameLoop::hacky_setup() {
  Model *cubeModel = new Model("models/suzy.obj");

  Shader *testShader = new Shader("shaders/shader.vert", "shaders/shader.frag");

  gl_handler_->add_model("cube", cubeModel);
  gl_handler_->add_shader("test", testShader);

  ModelInstance *instance = new ModelInstance(
    gl_handler_->get_model_id("cube"),
    gl_handler_->get_shader_id("test"));

  instance->setPosition(glm::vec3(0, .5, 0));
  instance->setRotation(glm::vec3(0, 1, 0), .5);

  game_state_->add_model_instance(instance);

  instance = new ModelInstance(
    gl_handler_->get_model_id("cube"),
    gl_handler_->get_shader_id("test"));

  instance->setPosition(glm::vec3(0, -3, 0));
  instance->setRotation(glm::vec3(0, 1, 0), 2);
  instance->setScale(glm::vec3(2, 2, 3));

  game_state_->add_model_instance(instance);
}

int GameLoop::run_game_loop() {
  SDL_Event event;

  hacky_setup(); // :(

  while (game_running_) {
    /*
     * TODO: Move controls to separate, observer based system.
     */
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
    SDL_Delay(1000.0f / FPS);
  }
  return 0;
}
