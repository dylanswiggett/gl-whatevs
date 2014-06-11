#ifndef _GAME_PHYSICS_OBJECT_HPP_
#define _GAME_PHYSICS_OBJECT_HPP_

#include "btBulletDynamicsCommon.h"
#include "GameObject.hpp"
#include "GamePhysicsState.hpp"
#include "glm/glm.hpp"

class GamePhysicsObject : public GameObject, public btMotionState {
 public:
  GamePhysicsObject(btCollisionShape *shape, double mass);
  virtual ~GamePhysicsObject();

  virtual void setPositionFixed(bool isFixed);

  virtual void getWorldTransform(btTransform &worldTrans) const override;
  virtual void setWorldTransform(const btTransform &wordTrans) override;

  virtual void addToPhysics(GamePhysicsState* physicsState);

 private:
  btCollisionShape* shape_;
  btRigidBody* body_;

  bool is_fixed_;
};

#endif  // _GAME_PHYSICS_OBJECT_HPP_