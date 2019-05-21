#ifndef PUZZLE_LEVEL_CONTROLLER_HPP
#define PUZZLE_LEVEL_CONTROLLER_HPP

#include <vector>
#include "SDL.h"
#include "game_manager.hpp"
#include "level_controller.hpp"
#include "level.hpp"
#include "sprite.hpp"
//#include "piece.hpp"
//#include "o_piece.hpp"
//#include "levels/puzzle_level.hpp"

class PuzzleLevel;

class PuzzleLevelController : public LevelController {
  public:
    PuzzleLevelController(PuzzleLevel*);
    ~PuzzleLevelController();
    void update(float);

  protected:
    PuzzleLevel *_puzzleLevel;
    bool pieceOnScreen();
    void deployPiece();
};

#endif
