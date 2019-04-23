#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "SDL.h"
#include "textured_sprite.hpp"
#include "game_manager.hpp"
#include "controller.hpp"
#include "hero_controller.hpp"

class Level {
  public:
    Level(SDL_Renderer*);
    ~Level();
    void update(float);
    void resolveCollisions();
    void render(SDL_Renderer*);
    void addSprite(Sprite*);

  protected:
    std::vector<Sprite*> _sprites;
    // e.g. the hero sprite is the only one
    // that needs to get input.
    // in Pengine2d i think i sent
    // controller input to all of them,
    // which is slower
    Sprite *_hero;
    SDL_Texture *_texture;

};
#endif
