#include "include/enemy_sprite_ellipsis.hpp"

EnemySpriteEllipsis::EnemySpriteEllipsis(RealPoint pos, SDL_Renderer* renderer, float a, float b) :
 EnemySprite(pos, renderer) {
   EllipseParametricFunctionController *cpfc =
      new EllipseParametricFunctionController(this, 100.0, 3.0, pos.X(), pos.Y(), a, b);
      //new EllipseParametricFunctionController(this, 100.0, 3.0, pos.X(), pos.Y(), 200.0, 25.0);
    cpfc->setLoop();
    cpfc->setLoopTolerance(0.15);
    this->_controller = cpfc;
}
