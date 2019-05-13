#ifndef SINE_ENEMIES_LEVEL_HPP
#define SINE_ENEMIES_LEVEL_HPP

#include <memory>
#include "SDL.h"
#include "../real_point.hpp"
#include "../game_manager.hpp"
#include "../level.hpp"
#include "../hero_sprite.hpp"
#include "../enemy_sprite_ellipsis.hpp"
#include "../enemy_sprite_sine.hpp"

class SineEnemiesLevel : public Level {
  public:
    SineEnemiesLevel(SDL_Renderer*);
    ~SineEnemiesLevel();
};
#endif
