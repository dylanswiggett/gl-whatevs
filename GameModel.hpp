#ifndef _GAME_MODEL_HPP_
#define _GAME_MODEL_HPP_

#include <map>
#include "GameObject.hpp"
#include "GamePhysicsState.hpp"

// Stores the actual state of the game, e.g.
// any interactive, physics, etc. elements.
// Anything related to graphical representation
// should not be involved here.
class GameModel {
 public:
  GameModel();
  ~GameModel();

  // Step the game state forward by the given number
  // of seconds.
  step(float seconds);
 private:
  std::map<GameObjectID,GameObject> game_objects_;
  GamePhysicsState* physics_state_;
};

#endif  // _GAME_MODEL_HPP_