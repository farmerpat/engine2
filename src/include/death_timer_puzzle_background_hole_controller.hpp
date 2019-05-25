#ifndef DEATH_TIMER_PUZZLE_BACKGROUND_HOLE_CONTROLLER_HPP
#define DEATH_TIMER_PUZZLE_BACKGROUND_HOLE_CONTROLLER_HPP

//#include "puzzle_background_hole.hpp"
#include "puzzle_background_hole_controller.hpp"

class PuzzleBackgroundHole;
//class PuzzleBackgroundHoleController;

class DeathTimerPuzzleBackgroundHoleController : public PuzzleBackgroundHoleController {
  public:
    DeathTimerPuzzleBackgroundHoleController(PuzzleBackgroundHole*, int);
    void update();

  protected:
    int _frameCounter = 0;
    int _framesToLive;

};
#endif
