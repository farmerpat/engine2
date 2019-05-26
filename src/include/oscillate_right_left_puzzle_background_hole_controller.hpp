#ifndef OSCILLATE_RIGHT_LEFT_PUZZLE_BACKGROUND_HOLE_CONTROLLER_HPP
#define OSCILLATE_RIGHT_LEFT_PUZZLE_BACKGROUND_HOLE_CONTROLLER_HPP

#include "real_point.hpp"
#include "puzzle_background_hole_controller.hpp"

class PuzzleBackgroundHole;

class OscillateRightLeftPuzzleBackgroundHoleController : public PuzzleBackgroundHoleController {
  public:
    OscillateRightLeftPuzzleBackgroundHoleController(PuzzleBackgroundHole*, int);
    void update();

  protected:
    int _frameCounter = 0;
    int _frameDelay = 60;
    int _moveSteps = 0;
    int _moveStepsCounter = 0;
    int _moveDirection = 1;

};
#endif
