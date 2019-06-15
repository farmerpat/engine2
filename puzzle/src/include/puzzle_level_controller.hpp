#ifndef PUZZLE_LEVEL_CONTROLLER_HPP
#define PUZZLE_LEVEL_CONTROLLER_HPP

#include <vector>
#include "SDL.h"
#include "include/game_manager.hpp"
#include "include/level_controller.hpp"
#include "include/level.hpp"
#include "include/sprite.hpp"
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
    // TODO:
    // decide if i want PuzzleLevel descendents to
    // deal with this type of thing
    int _missedHolesAllowed = 4;
    int _holesFilled = 0;
    int _holesMissed = 0;
};

#endif
