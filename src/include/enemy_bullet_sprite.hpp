#ifndef ENEMY_BULLET_SPRITE_HPP
#define ENEMY_BULLET_SPRITE_HPP

#include "SDL.h"
#include "real_point.hpp"
#include "textured_sprite.hpp"
#include "enemy_bullet_controller.hpp"

class EnemyBulletSprite : public TexturedSprite {
  public:
    EnemyBulletSprite(RealPoint, RealPoint, SDL_Renderer*);
};
#endif
