#ifndef ENEMY_SPRITE_HPP
#define ENEMY_SPRITE_HPP

#include "SDL.h"
#include "real_point.hpp"
#include "textured_sprite.hpp"
#include "ellipse_parametric_function_controller.hpp"

class EnemySprite : public TexturedSprite {
  public:
    // it might make sense to just take a more generic Controller* instead
    EnemySprite(RealPoint, SDL_Rect, SDL_Renderer*);
    void collisionHandler(Sprite*) override;
};
#endif