#ifndef _GAME_LOOP_HPP_
#define _GAME_LOOP_HPP_

#include <string>

#include "SDL2/SDL.h"
#include "GLHandler.hpp"
#include "GraphicsPipeline.hpp"
#include "GameModel.hpp"

class GameLoop {
 public:
  GameLoop(SDL_Window *window);
  ~GameLoop();

  int run_game_loop();
 private:
  void add_simple_game_object(std::string name, ModelInstance* instance);
  void add_simple_game_object(std::string name, ModelInstance* instance, GamePhysicsObject* obj);

  void hacky_setup();
  bool game_running_;
  GLHandler *gl_handler_;
  SDL_Window *window_;
  GraphicsPipeline *graphics_pipeline_;
  GameModel *game_model_;
};

#endif  // _GAME_LOOP_HPP_