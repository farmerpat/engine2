#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <memory>
#include <algorithm>
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
    void removeDeadSprites();
    void render(SDL_Renderer*);
    void addSprite(std::unique_ptr<Sprite>);
    std::unique_ptr<Sprite> &getSpriteByTag(std::string);

  protected:
    std::vector<std::unique_ptr<Sprite>> _sprites;
    Sprite *_hero;
    SDL_Texture *_texture;

};
#endif
