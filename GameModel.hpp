#ifndef _GAME_MODEL_HPP_
#define _GAME_MODEL_HPP_

#include <map>
#include <string>

#include "GameObject.hpp"
#include "GamePhysicsState.hpp"
#include "GamePhysicsObject.hpp"

// Stores the actual state of the game, e.g.
// any interactive, physics, etc. elements.
class GameModel {
 public:
  GameModel();
  ~GameModel();

  // Step the game state forward by the given number
  // of seconds.
  void step(float seconds);

  // Adds something to the game, that can be accessed either by the
  // name given or by the returned ID.
  GameObjectID addGameObject(std::string name, GameObject* obj);
  // Adds something to the game that can be accessed by the returned ID.
  GameObjectID addGameObject(GameObject* obj);

  GameObjectID addGamePhysicsObject(std::string name, GamePhysicsObject* obj);
  GameObjectID addGamePhysicsObject(GamePhysicsObject* obj);

  // Returns the GameObject with the given name, or nullptr
  // if no such object exists.
  GameObject* getGameObject(std::string name);
  // Returns the GameObject wih the given id, or nullptr
  // if no such object exists.
  GameObject* getGameObject(GameObjectID id);
 private:
  std::map<std::string,GameObjectID>* game_object_ids_;
  std::map<GameObjectID,GameObject *>* game_objects_;
  GamePhysicsState* physics_state_;
};

#endif  // _GAME_MODEL_HPP_