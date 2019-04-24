#include "parametric_function_controller.hpp"

ParametricFunctionController::ParametricFunctionController
(Sprite* s, double tmax, float scale = 1.0) :
  FunctionController(s) {
  this->_tScale = scale;
  this->_tMax = tmax;
}

void ParametricFunctionController::update(float dt) {
  this->_t += (dt * this->_tScale);

  if (this->_t >= this->_tMax) {
    this->_t = this->_tMax;
    this->_tScale *= -1.0;

  } else if (this->_t < 0) {
    this->_t = 0.0;
    this->_tScale *= -1.0;

  } 

  this->calculateX();
  this->calculateY();

  this->_sprite->setPos(this->_currentX, this->_currentY);
}
