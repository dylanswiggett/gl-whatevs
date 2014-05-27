#ifndef _GAME_MODEL_HPP_
#define _GAME_MODEL_HPP_

#include <map>
#include <string>

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
  void step(float seconds);

  GameObjectID addGameObject(std::string name, GameObject* obj);
  GameObjectID addGameObject(GameObject* obj);

  GameObject* getGameObject(std::string name);
  GameObject* getGameObject(GameObjectID id);
 private:
  std::map<std::string,GameObjectID>* game_object_ids_;
  std::map<GameObjectID,GameObject *>* game_objects_;
  GamePhysicsState* physics_state_;
};

#endif  // _GAME_MODEL_HPP_