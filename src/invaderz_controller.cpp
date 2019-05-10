#include "include/invaderz_controller.hpp"

InvaderzController::InvaderzController(MatrixOfSprites* sprite, int xmin, int xmax, float incx) {
  this->_sprite = sprite;
  this->_xMin = xmin;
  this->_xMax = xmax;
  this->_incX = incx;
  this->_movingRight = true;
}

InvaderzController::~InvaderzController() {
}

void InvaderzController::update(float dt) {
  RealPoint *pos = this->_sprite->getPos();
  float x = pos->X();

  if (this->_movingRight) {
    if (x < this->_xMax) {
      x += this->_incX;
      pos->setX(x);

    } else {
      this->_movingRight = false;

    }
  } else {
    if (x > this->_xMin) {
      x -= this->_incX;
      pos->setX(x);

    } else {
      this->_movingRight = true;

    }
  }
}
