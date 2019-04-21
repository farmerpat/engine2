#include "rectangular_primitive_sprite.hpp"
#include <iostream>

RectangularPrimitiveSprite::RectangularPrimitiveSprite(RealPoint p) :
  PrimitiveSprite(p) {
    this->_width = 10;
    this->_height = 10;
    this->_fillColor = new SDL_Color();
    this->_fillColor->r = 17;
    this->_fillColor->g = 249;
    this->_fillColor->b = 44;
    this->_fillColor->a = 255;

    this->_outlineColor = new SDL_Color();
    this->_outlineColor->r = 17;
    this->_outlineColor->g = 249;
    this->_outlineColor->b = 44;
    this->_outlineColor->a = 255;
}

RectangularPrimitiveSprite::RectangularPrimitiveSprite(RealPoint p, int w , int h) :
  PrimitiveSprite(p) {
    this->_width = w;
    this->_height = h;
    this->_fillColor = new SDL_Color();
    this->_fillColor->r = 17;
    this->_fillColor->g = 249;
    this->_fillColor->b = 44;
    this->_fillColor->a = 255;

    this->_outlineColor = new SDL_Color();
    this->_outlineColor->r = 17;
    this->_outlineColor->g = 249;
    this->_outlineColor->b = 44;
    this->_outlineColor->a = 255;
}

RectangularPrimitiveSprite::RectangularPrimitiveSprite(RealPoint p, int w , int h, SDL_Color c) :
  PrimitiveSprite(p) {
    this->_width = w;
    this->_height = h;

    this->_fillColor = new SDL_Color();
    this->_fillColor->r = c.r;
    this->_fillColor->g = c.g;
    this->_fillColor->b = c.b;
    this->_fillColor->a = c.a;

    this->_outlineColor = new SDL_Color();
    this->_outlineColor->r = 17;
    this->_outlineColor->g = 249;
    this->_outlineColor->b = 44;
    this->_outlineColor->a = 255;
}

void RectangularPrimitiveSprite::render(SDL_Renderer *renderer) {
  SDL_Rect rect;
  rect.x = (int)this->_pos->X();
  rect.y = (int)this->_pos->Y();
  rect.w = this->_width;
  rect.h = this->_height;

  //std::cout << (int)this->_pos->X() << std::endl;

  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;

  // this is bombing
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(
      renderer,
      this->_fillColor->r,
      this->_fillColor->g,
      this->_fillColor->b,
      this->_fillColor->a
  );

  if (_filled) {
    SDL_RenderFillRect(renderer, &rect);
  }

  SDL_SetRenderDrawColor(
      renderer,
      this->_outlineColor->r,
      this->_outlineColor->g,
      this->_outlineColor->b,
      this->_outlineColor->a
  );

  SDL_RenderDrawRect(renderer, &rect);

  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void RectangularPrimitiveSprite::setFilled() {
  _filled = true;
}

void RectangularPrimitiveSprite::clearFilled() {
  _filled = false;
}
