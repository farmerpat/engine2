#include "include/involute_of_a_circle_parametric_function_controller.hpp"

// TODO:
// radius may be a misnomer. learn to math and fix its name in parametric function controllers.
// its the "a" term e.g. in https://elepa.files.wordpress.com/2013/11/fifty-famous-curves.pdf
InvoluteOfACircleParametricFunctionController::InvoluteOfACircleParametricFunctionController
(Sprite* s, double tmax, float scale = 1.0, float xoff = 0, float yoff = 0, float radius = 1.0) :
ParametricFunctionController(s, tmax, scale) {
  this->_xOffset = xoff;
  this->_yOffset = yoff;
  this->_radius = radius;
}

void InvoluteOfACircleParametricFunctionController::calculateY() {
  this->_currentX = this->_radius * (cos(this->_t) + this->_t*sin(this->_t)) + this->_xOffset;
}

void InvoluteOfACircleParametricFunctionController::calculateX() {
  this->_currentY = this->_radius * (sin(this->_t) + this->_t*cos(this->_t)) + this->_yOffset;
}
