#include "include/shoot_if_hero_in_range_ai_controller.hpp"

ShootIfHeroInRangeAIController::ShootIfHeroInRangeAIController(Sprite *s) {
  Config config("config.ini");
  std::string shotDelayS = config.query("enemy_shot_delay");
  Uint32 shotDelay = std::stoi(shotDelayS);
  this->_frameShotDelay = shotDelay;

  std::string shotChanceS = config.query("enemy_shot_chance");
  float shotChance = std::stof(shotChanceS);
  this->_shotChance = shotChance;

  this->_sprite = s;
}

void ShootIfHeroInRangeAIController::update(float dt) {
  this->_frameShotDelayCounter++;

  if (this->_frameShotDelayCounter >= this->_frameShotDelay) {
    this->_canShoot = true;
  }

  GameManager *gm = GameManager::getInstance();

  if (gm) {
    if (gm->getHeroIsAlive()) {
      RealPoint *heroPos = gm->getHeroPos();
      int heroWidth = gm->getHeroWidth();
      RealPoint *myPos = this->_sprite->getPos();
      int myWidth = this->_sprite->getWidth() * this->_sprite->getXScale();
      int x = myPos->X() + myWidth / 2;

      if (_canShoot && x >= gm->getHeroPos()->X() && x <= gm->getHeroPos()->X() + heroWidth) {
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

          std::unique_ptr<Sprite> ebs = std::unique_ptr<Sprite>(
            new EnemyBulletSprite(bulletPos, vel, gm->getWindowRenderer())
          );

          gm->addSpriteToCurrentLevel(std::move(ebs));
          gm->playSound("assets/sounds/player_laser_shoot.wav");
          _canShoot = false;

          this->_frameShotDelayCounter = 0;

        }
      }
    }
  }
}

bool ShootIfHeroInRangeAIController::rngAllowShot() {
  bool canShoot = false;
  float rng = (rand() % 1001) / 1000.0;

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
