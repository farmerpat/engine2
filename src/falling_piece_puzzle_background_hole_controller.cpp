#include "include/falling_piece_puzzle_background_hole_controller.hpp"
#include "include/puzzle_background_hole.hpp"
#include <iostream>

FallingPieceBackgroundHoleController::FallingPieceBackgroundHoleController
(PuzzleBackgroundHole *hole, int frameDelay)
  : PuzzleBackgroundHoleController(hole) {
    this->_frameDelay = frameDelay;
}

void FallingPieceBackgroundHoleController::update() {
  this->_frameCounter++;

  if (this->_frameCounter >= this->_frameDelay) {
    GameManager *gm = GameManager::getInstance();

    if (gm) {
      int maxYPossible = gm->getIntFromDictionary("screenMatrixMaxY");
      this->_frameCounter = 0;

      RealPoint newPos = this->_hole->getMatrixPos();
      newPos.setY(newPos.Y() + this->_moveSize);
      this->_hole->setMatrixPos(newPos);

      if (newPos.Y() > maxYPossible) {
        this->_hole->kill();
        std::cout << "killing the hole\n";

      }
    }
  }
}
