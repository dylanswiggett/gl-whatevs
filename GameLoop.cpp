#include "GameLoop.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "shader_loader.hpp"
#include "glm/glm.hpp"
#include "Shader.hpp"
#include "FrameBufferShader.hpp"

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
  gl_handler_->add_model("suzanna", new Model("models/suzy.obj"));
  gl_handler_->add_model("smooth_suzanna", new Model("models/smooth_suzy.obj"));
  gl_handler_->add_model("cube", new Model("models/cube.obj"));
  gl_handler_->add_model("scene", new Model("models/hires_scene.obj"));
  gl_handler_->add_model("plane", new Model("models/plane.obj"));

  FrameBufferShader *fb_shad = new FrameBufferShader("shaders/squiggly.vert", "shaders/color_shader.frag", 0, 
      gl_handler_->get_width(), gl_handler_->get_height());

  gl_handler_->add_shader("default", new Shader("shaders/default.vert", "shaders/default.frag", .5));
  gl_handler_->add_shader("default_fb", new FrameBufferShader("shaders/default.vert", "shaders/default.frag", .1, *fb_shad));
  gl_handler_->add_shader("squiggly", new Shader("shaders/squiggly.vert", "shaders/default.frag", .5));
  gl_handler_->add_shader("crazy", new Shader("shaders/squiggly.vert", "shaders/color_shader.frag", .5));
  gl_handler_->add_shader("crazy_fb", fb_shad);

  Shader *post = new Shader("shaders/default_post.vert", "shaders/default_post.frag", 10);
  post->setTexture0(fb_shad->get_rendered_texture(), "rendered_tex");
  // post->setTexture1(fb_shad->get_depth_texture(), "depth_tex");
  gl_handler_->add_shader("post", post);

  ModelInstance *instance = new ModelInstance(
    gl_handler_->get_model("smooth_suzanna"),
    gl_handler_->get_shader_id("default_fb"));

  instance->setPosition(glm::vec3(0, .5, 0));
  instance->setRotation(glm::vec3(0, 1, 0), 200);
  instance->setScale(glm::vec3(4, 4, 4));

  game_state_->add_model_instance("suzanne", instance);

  instance = new ModelInstance(
    gl_handler_->get_model("plane"),
    gl_handler_->get_shader_id("post"));

  instance->setPosition(glm::vec3(0,0,0));
  instance->setScale(glm::vec3(.5,.5,.5));

  game_state_->add_model_instance("render_plane", instance);

  instance = new ModelInstance(
    gl_handler_->get_model("scene"),
    gl_handler_->get_shader_id("crazy_fb"));

  instance->setPosition(glm::vec3(0, -6, 2));
  instance->setRotation(glm::vec3(0, 1, 0), 60);
  instance->setScale(glm::vec3(2,2,2));

  game_state_->add_model_instance("scene", instance);

  instance = new ModelInstance(
    gl_handler_->get_model("plane"),
    gl_handler_->get_shader_id("squiggly"));

  instance->setPosition(glm::vec3(0, -3, 0));
  instance->setScale(glm::vec3(.5, .5, .5));

  game_state_->add_model_instance("cube", instance);

  // for (int x = -10; x <= 10; x++) {
  //   for (int y = -10; y <= 10; y++) {
  //     instance = new ModelInstance(
  //       gl_handler_->get_model("suzanna"),
  //       gl_handler_->get_shader_id("default"));

  //     instance->setPosition(glm::vec3(x, y, 5));
  //     instance->setScale(glm::vec3(.2, .2, .2));

  //     game_state_->add_model_instance("cube" + x + y, instance);
  //   }
  // }
}

int GameLoop::run_game_loop() {
  SDL_Event event;

  hacky_setup(); // :(

  float rot = 1000;

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
    game_state_->get_model_instance(game_state_->get_model_instance_id("scene"))->setRotation(glm::vec3(0, 1, 0), rot * .1);
    game_state_->get_model_instance(game_state_->get_model_instance_id("cube"))->setRotation(glm::vec3(1, 1, 0), -rot);
    rot += .4;

    game_state_->step();

    gl_handler_->clear_screen();

    game_state_->draw();

    SDL_GL_SwapWindow(window_);
    // SDL_Delay(1000.0f / FPS);
  }
  return 0;
}
