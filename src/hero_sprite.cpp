#include "include/hero_sprite.hpp"

HeroSprite::HeroSprite (RealPoint pos, SDL_Renderer *renderer) :
  TexturedSprite (pos, 32, 32, "assets/player_single_frame.png", renderer) {

  SDL_Rect hb;
  hb.x = 0;
  hb.y = 0;
  hb.w = 64;
  hb.h = 64;

  this->setHitBox(hb);
  this->setLayer(1);
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

  Config config("config.ini");
  std::string heroHpS = config.query("hero_hp");
  Uint32 heroHp = std::stoi(heroHpS);
  this->_hp = heroHp;

}

// bass class destructor is called automatically
HeroSprite::~HeroSprite () { }

void HeroSprite::collisionHandler(std::unique_ptr<Sprite> &other) {
  if (other->getTag() == "enemy_ship") {
    this->kill();

  } else if (other->getTag() == "enemy_bullet") {

    this->takeDamage();
    other->kill();

  }
}

void HeroSprite::takeDamage() {
  this->_hp--;

  if (this->_hp <= 0) {
    this->kill();
    GameManager *gm = GameManager::getInstance();

    if (gm) {
      gm->clearHeroIsAlive();

    }
  }
}
