#ifndef PUZZLE_LEVEL_HPP
#define PUZZLE_LEVEL_HPP

#include <memory>
#include "SDL.h"
#include "../real_point.hpp"
#include "../game_manager.hpp"
#include "../level.hpp"
#include "../sprite.hpp"
#include "../piece.hpp"

class PuzzleLevel : public Level {
  public:
    PuzzleLevel(SDL_Renderer*);
    ~PuzzleLevel();
};

#endif
