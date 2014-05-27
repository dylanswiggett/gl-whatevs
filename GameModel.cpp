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

GameObject* GameModel::getGameObject(string name) {
  return (*game_objects_)[(*game_object_ids_)[name]];
}

GameObject* GameModel::getGameObject(GameObjectID id) {
  return (*game_objects_)[id];
}
