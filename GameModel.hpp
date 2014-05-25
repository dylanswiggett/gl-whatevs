#ifndef _GAME_MODEL_HPP_
#define _GAME_MODEL_HPP_

#include <map>
#include "GameObject.hpp"
#include "GamePhysicsState.hpp"

class GameModel {
 public:
  GameModel();
  step();
 private:
  std::map<GameObjectID,GameObject>
  GamePhysicsState* physicsState;
};

#endif  // _GAME_MODEL_HPP_