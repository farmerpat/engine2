#include "include/player_bullet_controller.hpp"

PlayerBulletController::PlayerBulletController(Sprite *s) {
  this->_sprite = s;
}

void PlayerBulletController::update(float dt) {
  // TODO:
  // if the pos if off screen, flag the sprite for destruction
  this->_sprite->move(dt);
}
