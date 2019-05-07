#ifndef HERO_SPRITE_HPP
#define HERO_SPRITE_HPP

#include <memory>
#include "textured_sprite.hpp"
#include "hero_controller.hpp"

// TODO:
//  consider using a config.ini file that will
//  hold things like hero velocity, gravity ,drag etc.
//  this will allow us to alter magick numbers w/o
//  recompiling. could potentially alter in real time
//  as well, if we read from file instead of class memeber
class HeroSprite : public TexturedSprite {
  public:
    HeroSprite(RealPoint, SDL_Renderer*);
    ~HeroSprite();
    void collisionHandler(std::unique_ptr<Sprite>&) override;

  private:
    float moveSpeed = 10.0f;
    void takeDamage();

};
#endif
