#include "include/death_timer_puzzle_background_hole_controller.hpp"
#include "include/puzzle_background_hole.hpp"

DeathTimerPuzzleBackgroundHoleController::DeathTimerPuzzleBackgroundHoleController
  (PuzzleBackgroundHole *bhHole, int framesToLive) : PuzzleBackgroundHoleController(bhHole) {
  this->_framesToLive = framesToLive;
}

void DeathTimerPuzzleBackgroundHoleController::update() {
  this->_frameCounter++;

  if (this->_frameCounter >= this->_framesToLive) {
    this->_hole->kill();
    this->_active = false;
  }
}
