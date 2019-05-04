#include "enemy_sprite.hpp"

EnemySprite::EnemySprite
(RealPoint pos, SDL_Renderer *renderer) :
  TexturedSprite(pos, 16, 16, "../assets/enemy1_single_frame.png", renderer) {
    SDL_Rect hitBox;
    hitBox.x = 0;
    hitBox.y = 0;
    hitBox.w = 32;
    hitBox.h = 28;
    this->setHitBox(hitBox);
    this->setLayer(1);
    this->setTag("enemy_ship");
    this->setXScale(2);
    this->setYScale(2);

    ShootIfHeroInRangeAIController *aic = new ShootIfHeroInRangeAIController(this);
    this->_aiController = aic;
}

void EnemySprite::collisionHandler(Sprite *other) {
  if (other->getTag() == "player_bullet") {
    other->kill();
    this->kill();
  }
}
