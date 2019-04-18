#include "hero_controller.hpp"

HeroController::HeroController() { }

HeroController::HeroController(Sprite *sprite) {
  _sprite = sprite;
}

void HeroController::update(float dt) {
  GameManager *gm = GameManager::getInstance();

  int moveAmount = 10;

  if (gm) {
    if (gm->playerInput.upPressed) {
      // just change the velocity of the sprite.
      SDL_Point *newPos = this->_sprite->getPos();
      newPos->y -= moveAmount;
      this->_sprite->setPos(*newPos);

    } else if (gm->playerInput.downPressed) {
      SDL_Point *newPos = this->_sprite->getPos();
      newPos->y += moveAmount;
      this->_sprite->setPos(*newPos);

    } else if (gm->playerInput.leftPressed) {
      SDL_Point *newPos = this->_sprite->getPos();
      newPos->x -= moveAmount;
      this->_sprite->setPos(*newPos);

    } else if (gm->playerInput.rightPressed) {
      SDL_Point *newPos = this->_sprite->getPos();
      newPos->x += moveAmount;
      this->_sprite->setPos(*newPos);

    }
  }
}
