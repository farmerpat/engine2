#include "hero_sprite.hpp"

HeroSprite::HeroSprite (RealPoint pos, SDL_Renderer *renderer) :
  TexturedSprite (pos, 32, 32, "../assets/player_single_frame.png", renderer) {
  this->_controller = new HeroController(this);
  this->setBounded();
  this->setXScale(2);
  this->setYScale(2);
}

// bass class destructor is called automatically
HeroSprite::~HeroSprite () { }

void HeroSprite::collisionHandler(Sprite *other) {
  if (other->getTag() == "enemy_ship") {
    this->die();
  }
}

void HeroSprite::takeDamage() {

}

void HeroSprite::die() {
  this->clearActive();
}
