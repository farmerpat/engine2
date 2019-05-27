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

  int xMin = this->_xMin -
    (this->_sprite->getMatrix().getFirstNonEmptyColumnIndex()*
    (this->_sprite->getWidth()+this->_sprite->getXPad()));

  int xMax = this->_xMax +
    (((this->_sprite->getNumCols()-1) - this->_sprite->getMatrix().getLastNonEmptyColumnIndex())*
     (this->_sprite->getWidth()+this->_sprite->getXPad()));

  if (xMin!=-1 && xMax!=-1) {
    if (this->_movingRight) {
      if (x < xMax) {
        x += this->_incX;
        pos->setX(x);

      } else {
        this->_movingRight = false;

      }
    } else {
      if (x > xMin) {
        x -= this->_incX;
        pos->setX(x);

      } else {
        this->_movingRight = true;

      }
    }
  } else {
    this->_sprite->kill();
  }
}
