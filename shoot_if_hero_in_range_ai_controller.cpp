#include "shoot_if_hero_in_range_ai_controller.hpp"

ShootIfHeroInRangeAIController::ShootIfHeroInRangeAIController(Sprite *s) {
  this->_sprite = s;
}

void ShootIfHeroInRangeAIController::update(float dt) {
  // get the hero pos from gm, get our sprite's pos from _sprite,
  // if the center of our sprite , spawn an EnemyBulletSprite with a positive y velocity.
  // if it's not too soon. will add timer, but start with intense spam for POC
  GameManager *gm = GameManager::getInstance();

  if (gm) {
    Sprite *hero = gm->getHero();

    if (hero) {
      RealPoint *heroPos = hero->getPos();
      int heroWidth = hero->getWidth();
      RealPoint *myPos = this->_sprite->getPos();
      int myWidth = this->_sprite->getWidth() * this->_sprite->getXScale();
      int x = myPos->X() + myWidth / 2;

      if (x >= heroPos->X() && x <= heroPos->X() + heroWidth) {
        // TODO:
        // clean this up. we did some of the math above.
        RealPoint vel = { 0.0, 175.0 };
        RealPoint bulletPos;
        bulletPos.setX(this->_sprite->getPos()->X());
        bulletPos.setY(this->_sprite->getPos()->Y());
        bulletPos.setX(bulletPos.X()+(this->_sprite->getWidth() *.5 * this->_sprite->getXScale()) - 1);

        EnemyBulletSprite *ebs = new EnemyBulletSprite(bulletPos, vel, gm->getWindowRenderer());
        gm->addSpriteToCurrentLevel(ebs);
        gm->playSound("../assets/sounds/player_laser_shoot.wav");

        // get the level, add the sprite
      }
    }
  }
}
