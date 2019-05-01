#include "enemy_bullet_controller.hpp"

// TODO this could just be a bullet controller that only
// moves on update and deletes the sprite if off-screen
EnemyBulletController::EnemyBulletController(Sprite *s) {
  this->_sprite = s;
}

void EnemyBulletController::update(float dt) {
  // TODO:
  // if the pos if off screen, flag the sprite for destruction
  this->_sprite->move(dt);
}
