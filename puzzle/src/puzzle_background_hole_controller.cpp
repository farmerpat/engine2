#include "include/puzzle_background_hole_controller.hpp"

PuzzleBackgroundHoleController::PuzzleBackgroundHoleController(PuzzleBackgroundHole *hole) {
  this->_hole = hole;
}

void PuzzleBackgroundHoleController::update() { }

bool PuzzleBackgroundHoleController::isActive() {
  return this->_active;
}
