#include "archimedes_spiral_parametric_function_controller.hpp"

ArchimedesSpiralParametricFunctionController::ArchimedesSpiralParametricFunctionController
(Sprite* s, double tmax, float scale = 1.0, float xoff = 0, float yoff = 0) :
ParametricFunctionController(s, tmax, scale) {
  this->_xOffset = xoff;
  this->_yOffset = yoff;
}

void ArchimedesSpiralParametricFunctionController::calculateY() {
  this->_currentX = this->_t * cos(this->_t) + this->_xOffset;
}

void ArchimedesSpiralParametricFunctionController::calculateX() {
  this->_currentY = this->_t * sin(this->_t) + this->_yOffset;
}
