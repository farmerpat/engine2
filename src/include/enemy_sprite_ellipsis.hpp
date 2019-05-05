#ifndef ENEMY_SPRITE_ELLIPSIS_HPP
#define ENEMY_SPRITE_ELLIPSIS_HPP

#include "SDL.h"
#include "real_point.hpp"
#include "textured_sprite.hpp"
#include "ellipse_parametric_function_controller.hpp"
#include "enemy_sprite.hpp"

class EnemySpriteEllipsis : public EnemySprite {
  public:
    EnemySpriteEllipsis(RealPoint, SDL_Renderer*, float, float);
};
#endif
