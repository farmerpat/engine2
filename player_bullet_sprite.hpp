#ifndef PLAYER_BULLET_SPRITE_HPP
#define PLAYER_BULLET_SPRITE_HPP

#include "SDL.h"
#include "real_point.hpp"
#include "textured_sprite.hpp"
#include "player_bullet_controller.hpp"

class PlayerBulletSprite : public TexturedSprite {
  public:
    PlayerBulletSprite(RealPoint, RealPoint, SDL_Renderer*);
};
#endif
