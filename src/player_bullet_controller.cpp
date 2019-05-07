#include "include/player_bullet_controller.hpp"

PlayerBulletController::PlayerBulletController(Sprite *s) {
  this->_sprite = s;
}

void PlayerBulletController::update(float dt) {
  if (this->_sprite) {
    this->_sprite->move(dt);

    if (this->_sprite->offScreen()) {
      this->_sprite->kill();
    }
  }
}
