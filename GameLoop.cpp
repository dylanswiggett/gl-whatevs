#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "GameLoop.hpp"
#include "SDL2/SDL.h"
#include "shader_loader.hpp"
#include "Shader.hpp"
#include "FramebufferBinder.hpp"
#include "GraphicsPipeline.hpp"
#include "ModelInstancePositionUpdater.hpp"
#include "GameModel.hpp"
#include "btBulletDynamicsCommon.h"

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

void GameLoop::add_simple_game_object(std::string name, ModelInstance* instance, GamePhysicsObject* obj) {
  graphics_pipeline_->add_model_instance(name, instance);
  obj->addPositionUpdateSubscriber(new ModelInstancePositionUpdater(instance));
  game_model_->addGamePhysicsObject(name, obj);
}

void GameLoop::add_simple_game_object(std::string name, ModelInstance* instance) {
  graphics_pipeline_->add_model_instance(name, instance);
  GameObject* obj = new GameObject();
  obj->addPositionUpdateSubscriber(new ModelInstancePositionUpdater(instance));
  game_model_->addGameObject(name, obj);
}

/*
 * TODO: Make a better setup procedure!
 */
void GameLoop::hacky_setup() {
  // gl_handler_->add_model("suzanna", new Model("models/suzy.obj"));
  gl_handler_->add_model("smooth_suzanna", new Model("models/smooth_suzy.obj"));
  gl_handler_->add_model("cube", new Model("models/cube.obj"));
  gl_handler_->add_model("scene", new Model("models/hires_scene.obj"));
  gl_handler_->add_model("plane", new Model("models/plane.obj"));

  int w = gl_handler_->get_width();
  int h = gl_handler_->get_height();

  FramebufferBinder *shadow_buffer = new FramebufferBinder(1024, 1024, false, true);
  FramebufferBinder *fb = new FramebufferBinder(w, h, true, true);
  FramebufferBinder *fb2 = new FramebufferBinder(w, h, true, false);
  FramebufferBinder *screen_buffer = new FramebufferBinder(w, h);

  // Build the graphics pipeline.

  gl_handler_->add_graphics_item("draw_buffer", fb);
  graphics_pipeline_->add_graphics_step("draw_buffer", 0);

  gl_handler_->add_graphics_item("default",
      new Shader("shaders/default.vert", "shaders/default.frag", graphics_pipeline_->get_camera()));
  graphics_pipeline_->add_graphics_step("default", .5);

  Shader *red_shader = new Shader("shaders/default.vert", "shaders/color.frag", graphics_pipeline_->get_camera());
  red_shader->addInputParamf("r", 1);
  red_shader->addInputParamf("g", 0);
  red_shader->addInputParamf("b", 0);
  gl_handler_->add_graphics_item("red", red_shader);
  graphics_pipeline_->add_graphics_step("red", .5);

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

  add_simple_game_object("suzanne", instance);

  // ModelInstance *instance = new ModelInstance(
  //   gl_handler_->get_model("scene"),
  //   gl_handler_->get_graphics_item_id("default"));

  // instance->setPosition(glm::vec3(0, -6, 2));
  // instance->setRotation(glm::vec3(0, 1, 0), 2);
  // instance->setScale(glm::vec3(2,2,2));

  // add_simple_game_object("scene", instance);

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

  for (int i = 0; i < 100; i++) {

    std::string sh_name = "shader" + (char)i;

    float num = (i * 37) % 100;

    Shader *sh = new Shader("shaders/default.vert", "shaders/color.frag", graphics_pipeline_->get_camera());
    sh->addInputParamf("r", num * .01);
    sh->addInputParamf("g", 1.0 - num * .01);
    sh->addInputParamf("b", num * .01);
    gl_handler_->add_graphics_item(sh_name, sh);
    graphics_pipeline_->add_graphics_step(sh_name, .5);

    instance = new ModelInstance(
    gl_handler_->get_model("cube"),
    gl_handler_->get_graphics_item_id(sh_name));

    instance->setScale(glm::vec3(1, 1, 1 + num * .01));

    GamePhysicsObject *obj = new GamePhysicsObject(
      new btBoxShape(btVector3(btScalar(1),btScalar(1),btScalar(1 + num * .01))), 10.0);

    add_simple_game_object("box_test", instance, obj);

    int offset = (i % 10);

    obj->setPosition(glm::vec3(-.3 * offset, 2.1 * i, -.05 * offset));
  }

  instance = new ModelInstance(
  gl_handler_->get_model("cube"),
  gl_handler_->get_graphics_item_id("default"));

  instance->setScale(glm::vec3(20,1,20));

  GamePhysicsObject *obj2 = new GamePhysicsObject(
    new btBoxShape(btVector3(btScalar(20),btScalar(1),btScalar(20))), 0);

  add_simple_game_object("box_test", instance, obj2);

  obj2->setPosition(glm::vec3(0,-5,0));

  Shader *sh = new Shader("shaders/default.vert", "shaders/color.frag", graphics_pipeline_->get_camera());
  sh->addInputParamf("r", 0);
  sh->addInputParamf("g", 0);
  sh->addInputParamf("b", 0);
  gl_handler_->add_graphics_item("box_test_sh", sh);
  graphics_pipeline_->add_graphics_step("box_test_sh", .5);

  instance = new ModelInstance(
  gl_handler_->get_model("cube"),
  gl_handler_->get_graphics_item_id("box_test_sh"));

  instance->setScale(glm::vec3(3,1,3));

  obj2 = new GamePhysicsObject(
    new btBoxShape(btVector3(btScalar(3),btScalar(1),btScalar(3))), 0);

  add_simple_game_object("box_test_1", instance, obj2);

  obj2->setPosition(glm::vec3(0,-3,0));
}

int GameLoop::run_game_loop() {
  SDL_Event event;

  hacky_setup(); // :(

  float rot = 15;

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

    game_model_->step(.1);

    game_model_->getGameObject("suzanne")->setRotation(glm::vec3(0, 1, 0), rot);
    // game_model_->getGameObject("scene")->setRotation(glm::vec3(0, 1, 0), rot * .1);
    rot += .01;

    graphics_pipeline_->step();

    gl_handler_->clear_screen();

    graphics_pipeline_->draw();

    SDL_GL_SwapWindow(window_);
    // SDL_Delay(1000.0f / FPS);
  }
  return 0;
}
