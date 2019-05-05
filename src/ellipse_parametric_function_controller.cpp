#include "include/ellipse_parametric_function_controller.hpp"

EllipseParametricFunctionController::EllipseParametricFunctionController
(Sprite* s, double tmax, float scale = 1.0, float xoff = 0, float yoff = 0, float a = 1.0, float b = 1.0) :
ParametricFunctionController(s, tmax, scale) {
  this->_xOffset = xoff;
  this->_yOffset = yoff;
  this->_a = a;
  this->_b = b;
}

void EllipseParametricFunctionController::calculateY() {
  this->_currentX = this->_a * cos(this->_t) + this->_xOffset;
}

void EllipseParametricFunctionController::calculateX() {
  this->_currentY = this->_b * sin(this->_t) + this->_yOffset;
}
