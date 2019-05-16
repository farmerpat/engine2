#ifndef PUZZLE_LEVEL_HPP
#define PUZZLE_LEVEL_HPP

#include <memory>
#include "SDL.h"
#include "../real_point.hpp"
#include "../game_manager.hpp"
#include "../level.hpp"
#include "../sprite.hpp"
#include "../piece.hpp"
#include "../matrix_of_sprites.hpp"
#include "../level_controller.hpp"
#include "../puzzle_level_controller.hpp"

class PuzzleLevel : public Level {
  public:
    PuzzleLevel(SDL_Renderer*);
    ~PuzzleLevel();
    std::shared_ptr<MatrixOfSprites> getBackgroundMatrix();
    void render(SDL_Renderer*);

  protected:
    std::shared_ptr<MatrixOfSprites> _backgroundMatrix;

};

#endif
