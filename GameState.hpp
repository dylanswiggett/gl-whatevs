#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <map>

class GameState {
 public:
  GameState();
  ~GameState();

  void draw();
 private:
  map<int,ModelInstance *> modelInstances;
  Camera *currentCamera;
};

#endif // _GAME_STATE_HPP_