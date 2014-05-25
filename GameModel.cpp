#include "GameModel.hpp"
#include "GamePhysicsState.hpp"

GameModel::GameModel() {
  physics_state_ = new GamePhysicsState();
}

GameModel::~GameModel() {
  delete physics_state_;
}

void GameModel::step(float seconds) {
  physics_state_->step(seconds * 1000);
}
