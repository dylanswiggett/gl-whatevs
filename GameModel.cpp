#include <string>
#include <map>

#include "GameModel.hpp"
#include "GamePhysicsState.hpp"

using namespace std;

GameModel::GameModel() {
  physics_state_ = new GamePhysicsState();
  game_object_ids_ = new std::map<std::string,GameObjectID>();
  game_objects_ = new std::map<GameObjectID,GameObject *>();
}

GameModel::~GameModel() {
  delete physics_state_;
  // TODO: Delete all GameObjects
  delete game_object_ids_;
  delete game_objects_;
}

void GameModel::step(float seconds) {
  physics_state_->step(seconds * 1000);
}

GameObjectID GameModel::addGameObject(string name, GameObject* obj) {
  game_object_ids_->insert(pair<string,GameObjectID>(name,obj->getID()));
  return addGameObject(obj);
}

GameObjectID GameModel::addGameObject(GameObject* obj) {
  game_objects_->insert(pair<GameObjectID,GameObject*>(obj->getID(),obj));
  return obj->getID();
}

GameObjectID GameModel::addGamePhysicsObject(std::string name, GamePhysicsObject* obj) {
  obj->addToPhysics(physics_state_);
  return addGameObject(name, obj);
}

GameObjectID GameModel::addGamePhysicsObject(GamePhysicsObject* obj) {
  obj->addToPhysics(physics_state_);
  return addGameObject(obj);
}

GameObject* GameModel::getGameObject(string name) {
  map<string,GameObjectID>::iterator it = game_object_ids_->find(name);
  if (it == game_object_ids_->end())
    return nullptr;
  return (*game_objects_)[it->second];
}

GameObject* GameModel::getGameObject(GameObjectID id) {
  return (*game_objects_)[id];
}
