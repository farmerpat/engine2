#include "include/invaderz_ai_controller.hpp"
#include <iostream>

InvaderzAiController::InvaderzAiController(InvaderzMatrix* sprite) {
  this->_sprite = sprite;
  this->initMatrices();

  Config config("config.ini");
  std::string shotDelayS = config.query("enemy_shot_delay");
  Uint32 shotDelay = std::stoi(shotDelayS);
  this->_frameShotDelay = shotDelay;

  std::string shotChanceS = config.query("enemy_shot_chance");
  float shotChance = std::stof(shotChanceS);
  this->_shotChance = shotChance;

}

void InvaderzAiController::initMatrices() {
  int rows = this->_sprite->getNumRows();
  int cols = this->_sprite->getNumCols();

  for (int i=0; i<rows; i++) {
    this->_frameShotDelayCounterMatrix.push_back(std::vector<int>(cols, 0));
  }

  for (int i=0; i<rows; i++) {
    this->_canShootMatrix.push_back(std::vector<bool>(cols, true));
  }
}

void InvaderzAiController::updateFrameShotDelay() {
  const std::vector<std::vector<int>> mat = this->_sprite->getMatrix();
  int rows = this->_sprite->getNumRows();
  int cols = this->_sprite->getNumCols();

  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
      if (mat[i][j]) {
        this->_frameShotDelayCounterMatrix[i][j]++;

        if (this->_frameShotDelayCounterMatrix[i][j] >= this->_frameShotDelay) {
          this->_canShootMatrix[i][j] = true;

        }
      } else {
        // ignore the dead sprite somehow
      }
    }
  }
}

void InvaderzAiController::update(float dt) {
  this->updateFrameShotDelay();

  GameManager *gm = GameManager::getInstance();
  int rows = this->_sprite->getNumRows();
  int cols = this->_sprite->getNumCols();
  RealPoint shotVel = { 0.0, 175.0 };
  RealPoint bulletPos;

  if (gm && gm->getHeroIsAlive()) {
    RealPoint *heroPos = gm->getHeroPos();
    int heroX = gm->getHeroPos()->X();
    int heroWidth = gm->getHeroWidth();

    for (int i=0; i<rows; i++) {
      for (int j=0; j<cols; j++) {
        SDL_Rect hb = this->_sprite->getHitBoxAt(i, j);

        if (this->_canShootMatrix[i][j] && hb.x >= heroX && (hb.x <= heroX + heroWidth)) {
          if (this->rngAllowShot()) {
            bulletPos.setX(hb.x);
            bulletPos.setY(hb.y);
            bulletPos.setX(
              bulletPos.X() + (hb.w * .5) -1
            );

            bulletPos.setY(bulletPos.Y() + hb.h);

            std::unique_ptr<Sprite> ebs = std::unique_ptr<Sprite>(
              new EnemyBulletSprite(bulletPos, shotVel, gm->getWindowRenderer())
            );

            gm->addSpriteToCurrentLevel(std::move(ebs));
            gm->playSound("assets/sounds/player_laser_shoot.wav");

            this->_canShootMatrix[i][j] = false;
            this->_frameShotDelayCounterMatrix[i][j] = 0;

          }
        }
      }
    }
  }
}

bool InvaderzAiController::rngAllowShot() {
  bool canShoot = false;
  float rng = (rand() % 1001) / 1000.0;

  if (rng <= this->_shotChance) {
    canShoot = true;
  }

  return canShoot;
}
