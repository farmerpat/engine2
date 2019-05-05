#ifndef ENEMY_SPRITE_SINE_HPP
#define ENEMY_SPRITE_SINE_HPP

#include "SDL.h"
#include "real_point.hpp"
#include "textured_sprite.hpp"
#include "sine_function_of_x_controller.hpp"
#include "enemy_sprite.hpp"

class EnemySpriteSine : public EnemySprite {
  public:
    EnemySpriteSine(RealPoint, SDL_Renderer*, float, float);
};
#endif
