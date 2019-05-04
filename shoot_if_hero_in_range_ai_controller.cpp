#include "shoot_if_hero_in_range_ai_controller.hpp"

ShootIfHeroInRangeAIController::ShootIfHeroInRangeAIController(Sprite *s) {
  Config config("../config.ini");
  std::string shotDelayS = config.query("enemy_shot_delay");
  Uint32 shotDelay = std::stoi(shotDelayS);
  //this->_shotDelay = 3000;
  this->_shotDelay = shotDelay;

  std::string shotChanceS = config.query("enemy_shot_chance");
  float shotChance = std::stof(shotChanceS);
  this->_shotChance = shotChance;

  this->_sprite = s;
}

void ShootIfHeroInRangeAIController::update(float dt) {
  GameManager *gm = GameManager::getInstance();

  if (gm) {
    Sprite *hero = gm->getHero();

    if (hero) {
      RealPoint *heroPos = hero->getPos();
      int heroWidth = hero->getWidth();
      RealPoint *myPos = this->_sprite->getPos();
      int myWidth = this->_sprite->getWidth() * this->_sprite->getXScale();
      int x = myPos->X() + myWidth / 2;

      if (_canShoot && x >= heroPos->X() && x <= heroPos->X() + heroWidth) {
        if (this->rngAllowShot()) {
          // TODO:
          // clean this up. we did some of the math above.
          RealPoint vel = { 0.0, 175.0 };
          RealPoint bulletPos;
          bulletPos.setX(this->_sprite->getPos()->X());
          bulletPos.setY(this->_sprite->getPos()->Y());
          bulletPos.setX(
              bulletPos.X()+(this->_sprite->getWidth() *.5 * this->_sprite->getXScale()) - 1
              );

          bulletPos.setY(bulletPos.Y() + (this->_sprite->getHitBox()->h));

          EnemyBulletSprite *ebs = new EnemyBulletSprite(bulletPos, vel, gm->getWindowRenderer());
          gm->addSpriteToCurrentLevel(ebs);
          gm->playSound("../assets/sounds/player_laser_shoot.wav");
          _canShoot = false;
          this->_callbackTimerId = SDL_AddTimer(this->_shotDelay, this->timerCallBack, (void*)this);
        }

      }
    }
  }
}

bool ShootIfHeroInRangeAIController::rngAllowShot() {
  bool canShoot = false;
  float rng = (rand() % 101) / 100.0;

  if (rng <= this->_shotChance) {
    canShoot = true;
  }

  return canShoot;
}

Uint32 ShootIfHeroInRangeAIController::timerCallBack(Uint32 inteveral, void *thisPtr) {
  ShootIfHeroInRangeAIController *me = (ShootIfHeroInRangeAIController*)thisPtr;
  me->setCanShoot();
  me->removeTimer();
}

void ShootIfHeroInRangeAIController::setCanShoot() {
  this->_canShoot = true;
}

void ShootIfHeroInRangeAIController::clearCanShoot() {
  this->_canShoot = false;
}

void ShootIfHeroInRangeAIController::removeTimer() {
  SDL_RemoveTimer(this->_callbackTimerId);
}
