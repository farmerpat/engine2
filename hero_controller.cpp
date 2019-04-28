#include "hero_controller.hpp"

HeroController::HeroController() { }

HeroController::HeroController(Sprite *sprite) {
  _sprite = sprite;
}

void HeroController::update(float dt) {
  GameManager *gm = GameManager::getInstance();

  int moveAmount = 200;

  RealPoint oldVelocity(
    this->_sprite->getVelocity()->X(),
    this->_sprite->getVelocity()->Y()
  );

  if (gm) {
    if (gm->playerInput.leftPressed) {
      oldVelocity.setX(-moveAmount);

    } else if (gm->playerInput.rightPressed) {
      oldVelocity.setX(moveAmount);

    } else {
      oldVelocity.setX(0.0);

    }
  }

  this->_sprite->setVelocity(oldVelocity);
  this->_sprite->move(dt);

}
