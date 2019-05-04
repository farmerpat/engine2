#include "enemy_sprite_sine.hpp"

EnemySpriteSine::EnemySpriteSine(RealPoint pos, SDL_Renderer* renderer, float a, float f) :
  EnemySprite(pos, renderer) {
    // TODO:
    // makes more sense to pass RealPoint to FunctionController
    // constructor.
    SineFunctionOfXController *sfc =
      new SineFunctionOfXController(this, a, f);

    sfc->setMinX(30.0);
    sfc->setMaxX(530.0);
    // "speed"
    sfc->setXInc(2.5);
    sfc->setOscillating();

    this->_controller = sfc;
}
