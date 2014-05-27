#include <iostream>
#include "glm/glm.hpp"
#include "GameLoop.hpp"
#include "SDL2/SDL.h"
#include "shader_loader.hpp"
#include "Shader.hpp"
#include "FramebufferBinder.hpp"
#include "GraphicsPipeline.hpp"
#include "GameModel.hpp"

#define FPS 60

GameLoop::GameLoop(SDL_Window *window) :
  game_running_(true), window_(window)
{
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  gl_handler_ = new GLHandler(w, h);
  graphics_pipeline_ = new GraphicsPipeline(gl_handler_);
  game_model_= new GameModel();
}

GameLoop::~GameLoop() {
  delete graphics_pipeline_;
  delete game_model_;
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
  FramebufferBinder *fb2 = new FramebufferBinder(w, h, true, false);
  FramebufferBinder *screen_buffer = new FramebufferBinder(w, h);

  // Build the graphics pipeline.

  gl_handler_->add_graphics_item("draw_buffer", fb);
  graphics_pipeline_->add_graphics_step("draw_buffer", 0);

  gl_handler_->add_graphics_item("default",
      new Shader("shaders/default.vert", "shaders/default.frag", graphics_pipeline_->get_camera()));
  graphics_pipeline_->add_graphics_step("default", .5);

  gl_handler_->add_graphics_item("squiggly",
      new Shader("shaders/squiggly.vert", "shaders/default.frag", graphics_pipeline_->get_camera()));
  graphics_pipeline_->add_graphics_step("squiggly", .5);

  gl_handler_->add_graphics_item("crazy",
      new Shader("shaders/squiggly.vert", "shaders/color_shader.frag", graphics_pipeline_->get_camera()));
  graphics_pipeline_->add_graphics_step("crazy", .5);

  gl_handler_->add_graphics_item("edge_buffer", fb2);
  graphics_pipeline_->add_graphics_step("edge_buffer", 5);

  Shader *edge = new Shader("shaders/default_post.vert", "shaders/edge_detect.frag", graphics_pipeline_->get_camera());
  edge->setTexture0(fb->get_color_texture(), "rendered_tex");
  gl_handler_->add_graphics_item("edge_renderer", edge);
  graphics_pipeline_->add_graphics_step("edge_renderer", 10);

  gl_handler_->add_graphics_item("default_buffer", screen_buffer);
  graphics_pipeline_->add_graphics_step("default_buffer", 11);

  Shader *post = new Shader("shaders/default_post.vert", "shaders/default_post.frag", graphics_pipeline_->get_camera());
  post->setTexture0(fb2->get_color_texture(), "rendered_tex");
  post->setTexture1(fb->get_depth_texture(), "depth_tex");
  gl_handler_->add_graphics_item("post_renderer", post);
  graphics_pipeline_->add_graphics_step("post_renderer", 12);

  // Add models to the scene.

  ModelInstance *instance = new ModelInstance(
    gl_handler_->get_model("smooth_suzanna"),
    gl_handler_->get_graphics_item_id("squiggly"));

  instance->setPosition(glm::vec3(0, .5, 0));
  instance->setRotation(glm::vec3(0, 1, 0), 200);
  instance->setScale(glm::vec3(4, 4, 4));

  graphics_pipeline_->add_model_instance("suzanne", instance);

  instance = new ModelInstance(
    gl_handler_->get_model("scene"),
    gl_handler_->get_graphics_item_id("default"));

  instance->setPosition(glm::vec3(0, -6, 2));
  instance->setRotation(glm::vec3(0, 1, 0), 60);
  instance->setScale(glm::vec3(2,2,2));

  graphics_pipeline_->add_model_instance("scene", instance);

  instance = new ModelInstance(
    gl_handler_->get_model("plane"),
    gl_handler_->get_graphics_item_id("edge_renderer"));

  instance->setPosition(glm::vec3(0,0,0));
  instance->setScale(glm::vec3(.5,.5,.5));

  graphics_pipeline_->add_model_instance("edge_render_plane", instance);

  // Final plane to draw to screen (everything rendered on this.)

  instance = new ModelInstance(
    gl_handler_->get_model("plane"),
    gl_handler_->get_graphics_item_id("post_renderer"));

  instance->setPosition(glm::vec3(0,0,0));
  instance->setScale(glm::vec3(.5,.5,.5));

  graphics_pipeline_->add_model_instance("render_plane", instance);
}

int GameLoop::run_game_loop() {
  SDL_Event event;

  hacky_setup(); // :(

  float rot = 5;

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
    graphics_pipeline_->get_model_instance(graphics_pipeline_->get_model_instance_id("suzanne"))->setRotation(glm::vec3(0, 1, 0), rot);
    graphics_pipeline_->get_model_instance(graphics_pipeline_->get_model_instance_id("scene"))->setRotation(glm::vec3(0, 1, 0), rot * .1);
    // graphics_pipeline_->get_model_instance(graphics_pipeline_->get_model_instance_id("cube"))->setRotation(glm::vec3(1, 1, 0), -rot);
    rot += .01;

    graphics_pipeline_->step();

    gl_handler_->clear_screen();

    graphics_pipeline_->draw();

    SDL_GL_SwapWindow(window_);
    // SDL_Delay(1000.0f / FPS);
  }
  return 0;
}
