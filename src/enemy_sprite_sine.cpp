#include "include/enemy_sprite_sine.hpp"

EnemySpriteSine::EnemySpriteSine
(RealPoint pos, SDL_Renderer* renderer, float a, float f, float minx, float maxx) :
  EnemySprite(pos, renderer) {
    // TODO:
    // makes more sense to pass RealPoint to FunctionController
    // constructor.
    SineFunctionOfXController *sfc =
      new SineFunctionOfXController(this, a, f);

    sfc->setMinX(minx);
    sfc->setMaxX(maxx);
    // "speed"
    //sfc->setXInc(2.5);
    sfc->setXInc(1.0);
    sfc->setOscillating();

    this->_controller = sfc;
}
