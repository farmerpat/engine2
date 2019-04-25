#include "circle_parametric_function_controller.hpp"

CircleParametricFunctionController::CircleParametricFunctionController
(Sprite* s, double tmax, float scale = 1.0, float xoff = 0, float yoff = 0, float radius = 1.0) :
ParametricFunctionController(s, tmax, scale) {
  this->_xOffset = xoff;
  this->_yOffset = yoff;
  this->_radius = radius;
}

void CircleParametricFunctionController::calculateY() {
  this->_currentX = this->_radius * cos(this->_t) + this->_xOffset;
}

void CircleParametricFunctionController::calculateX() {
  this->_currentY = this->_radius * sin(this->_t) + this->_yOffset;
}
