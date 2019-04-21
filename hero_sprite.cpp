#include "hero_sprite.hpp"

HeroSprite::HeroSprite (RealPoint pos, SDL_Renderer *renderer) :
  TexturedSprite (pos, 32, 32, "./slug_right.png", renderer) {
  this->controller = new HeroController(this);
}

// bass class destructor is called automatically
HeroSprite::~HeroSprite () { }
