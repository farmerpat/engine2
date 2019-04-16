#ifndef HERO_SPRITE_HPP
#define HERO_SPRITE_HPP

#include "textured_sprite.hpp"
#include "hero_controller.hpp"

class HeroSprite : public TexturedSprite {
  public:
    HeroSprite(SDL_Point, SDL_Renderer*);
    ~HeroSprite();

  private:
    float moveSpeed = 10.0f;
    SDL_Point velocity { 0, 0 };

};
#endif
