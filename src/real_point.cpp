#include "include/real_point.hpp"

RealPoint::RealPoint() { }

RealPoint::RealPoint(float x, float y) {
  this->_x = x;
  this->_y = y;
}

float RealPoint::X() const {
  return this->_x;
}

float RealPoint::Y() const {
  return this->_y;
}

void RealPoint::setX (float x) {
  this->_x = x;
}

void RealPoint::setY (float y) {
  this->_y = y;
}

SDL_Point *RealPoint::toSdlPoint() {
  SDL_Point *p = new SDL_Point();
  p->x = (int)this->_x;
  p->y = (int)this->_y;
  return p;
}
