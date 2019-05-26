#include "include/oscillate_right_left_puzzle_background_hole_controller.hpp"
#include "include/puzzle_background_hole.hpp"

OscillateRightLeftPuzzleBackgroundHoleController::OscillateRightLeftPuzzleBackgroundHoleController
(PuzzleBackgroundHole *hole, int moveSteps) : PuzzleBackgroundHoleController(hole) {
  this->_moveSteps = moveSteps;
}

// TODO:
// this moves up/down instead. figure out why x/y are reversed
// and fix it.
void OscillateRightLeftPuzzleBackgroundHoleController::update() {
  this->_frameCounter++;

  if (this->_frameCounter >= this->_frameDelay) {
    this->_frameCounter = 0;

    // TODO: there are _moveSteps moves the first time.
    // then _moveSteps - 1. fix it.
    if (this->_moveStepsCounter > this->_moveSteps) {
      this->_moveStepsCounter = 0;
      this->_moveDirection *= -1;

    } else {
      // add 1*moveDir to _hole's x
      RealPoint newPos = this->_hole->getMatrixPos();
      newPos.setX(newPos.X() + this->_moveDirection);
      this->_hole->setMatrixPos(newPos);
    }

    this->_moveStepsCounter++;
  }
}
