#include "function_controller.hpp"

FunctionController::FunctionController(Sprite *s) {
  this->_sprite = s;
  this->_initialX = s->getPos()->X();
  this->_initialY = s->getPos()->Y();
  this->_currentX = this->_initialX;
  this->_currentY = this->_initialY;
}

// NOTE:
//  overridden constructors can also base values off of
//  screen width/height since they've been added to GameManager
void FunctionController::update(float dt) {
  // we would need to know the order of these
  if (this->_yDependsOnX) {
    this->calculateX();
    this->calculateY();

  } else {
    this->calculateY();
    this->calculateX();

  }

  this->_sprite->setPos(this->_currentX, this->_currentY);
}

void FunctionController::calculateY() {
  if (this->_yInc) {
    this->_currentY += this->_yInc;

    if (this->_currentY >= this->_maxY) {
      this->_currentY = this->_maxY;

      if (this->_oscillating) {
        this->_yInc *= -1.0;

      } else {
        this->_yInc = 0.0;
      }
    } else if (this->_currentY <= this->_minY) {
      this->_currentY = this->_minY;

      if (this->_oscillating) {
        this->_yInc *= -1.0;

      } else {
        this->_yInc = 0.0;
      }
    }
  }
}

void FunctionController::calculateX() {
  if (this->_xInc) {
    this->_currentX += this->_xInc;

    if (this->_currentX >= this->_maxX) {
      this->_currentX = this->_maxX;

      if (this->_oscillating) {
        this->_xInc *= -1.0;
      } else {
        this->_xInc = 0.0;
      }
    } else if (this->_currentX <= this->_minX) {
      this->_currentX = this->_minX;

      if (this->_oscillating) {
        this->_xInc *= -1.0;
      } else {
        this->_xInc = 0.0;
      }
    }
  }
}

void FunctionController::setYDependsOnX() {
  this->_yDependsOnX = true;
}

void FunctionController::clearYDependsOnX() {
  this->_yDependsOnX = false;
}

void FunctionController::setInitialX(float x) {
  this->_initialX = x;
}

void FunctionController::setInitialY(float y) {
  this->_initialY = y;
}

void FunctionController::setMinX(float x) {
  this->_minX = x;
}

void FunctionController::setMinY(float y) {
  this->_minY = y;
}

void FunctionController::setMaxX(float x) {
  this->_maxX = x;
}

void FunctionController::setMaxY(float y) {
  this->_maxY = y;
}

void FunctionController::setXInc(float x) {
    this->_xInc = x;
}

void FunctionController::setYInc(float y) {
  this->_yInc = y;
}

void FunctionController::setOscillating() {
  this->_oscillating = true;
}
void FunctionController::clearOscillating() {
  this->_oscillating = false;
}
