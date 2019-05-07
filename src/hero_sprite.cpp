#include "include/hero_sprite.hpp"

HeroSprite::HeroSprite (RealPoint pos, SDL_Renderer *renderer) :
  TexturedSprite (pos, 32, 32, "../assets/player_single_frame.png", renderer) {
  this->_controller = new HeroController(this);
  this->setBounded();
  this->setXScale(2);
  this->setYScale(2);
  this->setTag("hero");

  GameManager *gm = GameManager::getInstance();

  if (gm) {
    gm->setHeroPos(this->_pos);
    // TODO:
    // why doesn't getWidth just calculate this for us?
    // there are a few places where that would need updated.
    gm->setHeroWidth(this->_width*this->_xScale);
    gm->setHeroHeight(this->_height*this->_yScale);
    gm->setHeroIsAlive();
  }
}

// bass class destructor is called automatically
HeroSprite::~HeroSprite () { }

void HeroSprite::collisionHandler(std::unique_ptr<Sprite> &other) {
  if (other->getTag() == "enemy_ship" ||
      other->getTag() == "enemy_bullet") {

    this->kill();
    if (other->getTag() == "enemy_bullet") {
      other->kill();
    }

    GameManager *gm = GameManager::getInstance();

    if (gm) {
      gm->clearHeroIsAlive();

    }
  }
}

void HeroSprite::takeDamage() {

}
