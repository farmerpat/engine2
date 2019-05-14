#ifndef PUZZLE_LEVEL_CONTROLLER_HPP
#define PUZZLE_LEVEL_CONTROLLER_HPP

#include <vector>
#include "SDL.h"
#include "game_manager.hpp"
#include "level_controller.hpp"
#include "level.hpp"
#include "sprite.hpp"
#include "piece.hpp"

class PuzzleLevelController : public LevelController {
  public:
    PuzzleLevelController(Level*);
    ~PuzzleLevelController();
    void update(float);

  protected:
    bool pieceOnScreen();
    void deployPiece();
};

#endif
