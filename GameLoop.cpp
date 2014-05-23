#include "GameLoop.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "shader_loader.hpp"
#include "glm/glm.hpp"
#include "Shader.hpp"
#include "FramebufferBinder.hpp"

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
  // gl_handler_->add_model("suzanna", new Model("models/suzy.obj"));
  gl_handler_->add_model("smooth_suzanna", new Model("models/smooth_suzy.obj"));
  // gl_handler_->add_model("cube", new Model("models/cube.obj"));
  gl_handler_->add_model("scene", new Model("models/hires_scene.obj"));
  gl_handler_->add_model("plane", new Model("models/plane.obj"));

  int w = gl_handler_->get_width();
  int h = gl_handler_->get_height();

  FramebufferBinder *fb = new FramebufferBinder(w, h, true, true);
  FramebufferBinder *screen_buffer = new FramebufferBinder(w, h);

  // Build the graphics pipeline.

  gl_handler_->add_graphics_item("draw_buffer", fb);
  game_state_->add_graphics_step("draw_buffer", 0);

  gl_handler_->add_graphics_item("default",
      new Shader("shaders/default.vert", "shaders/default.frag", game_state_->get_camera()));
  game_state_->add_graphics_step("default", .5);

  gl_handler_->add_graphics_item("squiggly",
      new Shader("shaders/squiggly.vert", "shaders/default.frag", game_state_->get_camera()));
  game_state_->add_graphics_step("squiggly", .5);

  gl_handler_->add_graphics_item("crazy",
      new Shader("shaders/squiggly.vert", "shaders/color_shader.frag", game_state_->get_camera()));
  game_state_->add_graphics_step("crazy", .5);

  gl_handler_->add_graphics_item("default_buffer", screen_buffer);
  game_state_->add_graphics_step("default_buffer", 5);

  // Shader *post = new Shader("shaders/default_post.vert", "shaders/default_post.frag", game_state_->get_camera());
  // post->setTexture0(fb->get_color_texture(), "rendered_tex");
  // post->setTexture1(fb->get_depth_texture(), "depth_tex");
  // gl_handler_->add_graphics_item("post_renderer", post);
  // game_state_->add_graphics_step("post_renderer", 10);

  Shader *post = new Shader("shaders/default_post.vert", "shaders/edge_detect.frag", game_state_->get_camera());
  post->setTexture0(fb->get_color_texture(), "rendered_tex");
  post->setTexture1(fb->get_depth_texture(), "depth_tex");
  gl_handler_->add_graphics_item("post_renderer", post);
  game_state_->add_graphics_step("post_renderer", 10);

  // Add models to the scene.

  ModelInstance *instance = new ModelInstance(
    gl_handler_->get_model("smooth_suzanna"),
    gl_handler_->get_graphics_item_id("squiggly"));

  instance->setPosition(glm::vec3(0, .5, 0));
  instance->setRotation(glm::vec3(0, 1, 0), 200);
  instance->setScale(glm::vec3(4, 4, 4));

  game_state_->add_model_instance("suzanne", instance);

  instance = new ModelInstance(
    gl_handler_->get_model("scene"),
    gl_handler_->get_graphics_item_id("default"));

  instance->setPosition(glm::vec3(0, -6, 2));
  instance->setRotation(glm::vec3(0, 1, 0), 60);
  instance->setScale(glm::vec3(2,2,2));

  game_state_->add_model_instance("scene", instance);

  // Final plane to draw to screen (everything rendered on this.)

  instance = new ModelInstance(
    gl_handler_->get_model("plane"),
    gl_handler_->get_graphics_item_id("post_renderer"));

  instance->setPosition(glm::vec3(0,0,0));
  instance->setScale(glm::vec3(.5,.5,.5));

  game_state_->add_model_instance("render_plane", instance);
}

int GameLoop::run_game_loop() {
  SDL_Event event;

  hacky_setup(); // :(

  float rot = 1;

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
    // game_state_->get_model_instance(game_state_->get_model_instance_id("cube"))->setRotation(glm::vec3(1, 1, 0), -rot);
    rot += .01;

    game_state_->step();

    gl_handler_->clear_screen();

    game_state_->draw();

    SDL_GL_SwapWindow(window_);
    // SDL_Delay(1000.0f / FPS);
  }
  return 0;
}
