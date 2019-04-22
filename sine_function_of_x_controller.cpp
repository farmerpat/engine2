#include "sine_function_of_x_controller.hpp"

SineFunctionOfXController::SineFunctionOfXController(Sprite *s, float a=1.0, float f=1.0) :
  FunctionController(s) {
  this->_amplitude = a;
  this->_frequency = f;
}


void SineFunctionOfXController::calculateY() {
  float val = this->_amplitude*sin(this->_frequency*this->_currentX) + this->_initialY;
  this->_currentY = val;

}
