#ifndef FALLING_PIECE_BACKGROUND_HOLE_CONTROLLER_HPP
#define FALLING_PIECE_BACKGROUND_HOLE_CONTROLLER_HPP

#include "include/real_point.hpp"
#include "include/game_manager.hpp"
#include "include/puzzle_background_hole_controller.hpp"

class PuzzleBackgroundHole;

class FallingPieceBackgroundHoleController : public PuzzleBackgroundHoleController  {
  public:
    FallingPieceBackgroundHoleController(PuzzleBackgroundHole*, int=60);
    void update();

  protected:
    int _frameCounter = 0;
    int _frameDelay = 60;
    int _moveSize = 1;

};

#endif
