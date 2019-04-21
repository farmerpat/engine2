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
    if (gm->playerInput.upPressed) {
      oldVelocity.setY(-moveAmount);
      //RealPoint *newPos = this->_sprite->getPos();
      //newPos->setY(newPos->Y() - moveAmount);
      //this->_sprite->setPos(*newPos);

    } else if (gm->playerInput.downPressed) {
      oldVelocity.setY(moveAmount);
      //RealPoint *newPos = this->_sprite->getPos();
      //newPos->setY(newPos->Y() + moveAmount);
      //this->_sprite->setPos(*newPos);

    } else if (gm->playerInput.leftPressed) {
      oldVelocity.setX(-moveAmount);
      //RealPoint *newPos = this->_sprite->getPos();
      //newPos->setX(newPos->X() - moveAmount);
      //this->_sprite->setPos(*newPos);

    } else if (gm->playerInput.rightPressed) {
      oldVelocity.setX(moveAmount);
      //RealPoint *newPos = this->_sprite->getPos();
      //newPos->setX(newPos->X() + moveAmount);
      //this->_sprite->setPos(*newPos);

    } else {
      oldVelocity.setX(0.0);
      oldVelocity.setY(0.0);

    }


  }

  this->_sprite->setVelocity(oldVelocity);
  this->_sprite->move(dt);

  // can we call parent update?
  // even if so, is it better to leave
  // controllers enough flexibility
  // to update at their will, or
  // would responding to velocity be good enough?
}
