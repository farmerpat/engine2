#ifndef PUZZLE_BACKGROUND_HOLE_CONTROLLER_HPP
#define PUZZLE_BACKGROUND_HOLE_CONTROLLER_HPP

#include "puzzle_background_hole.hpp"
class PuzzleBackgroundHole;

class PuzzleBackgroundHoleController {
  public:
    PuzzleBackgroundHoleController(PuzzleBackgroundHole*);
    virtual void update() {};

  protected:
    PuzzleBackgroundHole *_hole = 0;
};
#endif
