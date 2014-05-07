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
  Model *suzanneModel = new Model("models/suzy.obj");
  Model *cubeModel = new Model("models/cube.obj");

  Shader *testShader = new Shader("shaders/shader.vert", "shaders/shader.frag");

  gl_handler_->add_model("suzanna", suzanneModel);
  gl_handler_->add_model("cube", cubeModel);

  gl_handler_->add_shader("test", testShader);

  ModelInstance *instance = new ModelInstance(
    gl_handler_->get_model_id("suzanna"),
    gl_handler_->get_shader_id("test"));

  instance->setPosition(glm::vec3(0, .5, 0));
  instance->setRotation(glm::vec3(0, 1, 0), .5);
  instance->setScale(glm::vec3(4, 4, 4));

  game_state_->add_model_instance("suzanne", instance);

  instance = new ModelInstance(
    gl_handler_->get_model_id("cube"),
    gl_handler_->get_shader_id("test"));

  instance->setPosition(glm::vec3(0, -3, 0));
  instance->setScale(glm::vec3(.5, .5, .5));

  game_state_->add_model_instance("cube", instance);

  for (int x = -10; x <= 10; x++) {
    for (int y = -10; y <= 10; y++) {
      instance = new ModelInstance(
        gl_handler_->get_model_id("cube"),
        gl_handler_->get_shader_id("test"));

      instance->setPosition(glm::vec3(x, y, 5));
      instance->setScale(glm::vec3(.2, .2, .2));

      game_state_->add_model_instance("cube", instance);
    }
  }
}

int GameLoop::run_game_loop() {
  SDL_Event event;

  hacky_setup(); // :(

  float rot = 0;

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

    game_state_->get_model_instance(game_state_->get_model_instance_id("suzanne"))->setRotation(glm::vec3(0, 1, 0), rot);
    game_state_->get_model_instance(game_state_->get_model_instance_id("cube"))->setRotation(glm::vec3(1, 1, 0), -rot);
    rot += .4;

    game_state_->step();

    gl_handler_->clear_screen();

    game_state_->draw();

    SDL_GL_SwapWindow(window_);
    SDL_Delay(1000.0f / FPS);
  }
  return 0;
}
