#include "include/primitive_sprite.hpp"

PrimitiveSprite::PrimitiveSprite(RealPoint p)
  : Sprite(p) {
}

PrimitiveSprite::~PrimitiveSprite() {
  if (this->_fillColor) {
    delete this->_fillColor;
  }

  if (this->_outlineColor) {
    delete this->_outlineColor;
  }
}

void PrimitiveSprite::render(SDL_Renderer* renderer) {
  // draw it somehow
  // want path object?
}
