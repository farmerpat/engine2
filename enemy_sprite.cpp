#include "enemy_sprite.hpp"

EnemySprite::EnemySprite
(RealPoint pos, SDL_Rect hitBox, SDL_Renderer *renderer) :
  TexturedSprite(pos, 16, 16, "../assets/enemy1_single_frame.png", renderer) {

    this->setHitBox(hitBox);
    this->setLayer(1);
    this->setTag("enemy_ship");
    this->setXScale(2);
    this->setYScale(2);

    EllipseParametricFunctionController *cpfc =
      new EllipseParametricFunctionController(this, 100.0, 3.0, pos.X(), pos.Y(), 200.0, 25.0);
    cpfc->setLoop();
    cpfc->setLoopTolerance(0.15);
    this->_controller = cpfc;

    ShootIfHeroInRangeAIController *aic = new ShootIfHeroInRangeAIController(this);
    this->_aiController = aic;
}

void EnemySprite::collisionHandler(Sprite *other) {
  if (other->getTag() == "player_bullet") {
    other->kill();
    this->kill();
  }
}
