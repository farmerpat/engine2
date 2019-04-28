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

    if (gm->playerInput.aJustPressed) {
      // fire if we can (e.g. add time constraint later)
      RealPoint vel = { 0.0, -175.0 };
      RealPoint pos;
      pos.setX(this->_sprite->getPos()->X());
      pos.setY(this->_sprite->getPos()->Y());
      pos.setX(pos.X()+(this->_sprite->getWidth() *.5 * this->_sprite->getXScale()) - 1);
      PlayerBulletSprite *bullet = new PlayerBulletSprite(pos, vel, gm->getWindowRenderer());

      gm->addSpriteToCurrentLevel(bullet);
    }
  }

  this->_sprite->setVelocity(oldVelocity);
  this->_sprite->move(dt);

}
