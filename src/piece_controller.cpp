#include "include/piece_controller.hpp"

PieceController::PieceController(Piece *p) {
  this->_piece = p;
}

void PieceController::update(float dt) {
  this->_gravityFrameCounter++;
  GameManager *gm = GameManager::getInstance();
  int move = 0;

  RealPoint newPos(
    this->_piece->getPos()->X(),
    this->_piece->getPos()->Y()
  );

  if (gm) {
    if (gm->playerInput.leftJustPressed) {
      move = -this->_moveSize;

    } else if (gm->playerInput.rightJustPressed) {
      move = this->_moveSize;

    }

    if (gm->playerInput.aJustPressed) {
      // somehow set the correct blocks
      // in the background, and clear
      // the corresponding blocks in this->_piece
    }
  }

  // keep this in bounds
  newPos.setX(newPos.X()+move);

  if (this->_gravityFrameCounter >= this->_gravityFrameDelay) {
    this->_gravityFrameCounter = 0;
    newPos.setY(newPos.Y()+this->_gravity);
  }

  this->_piece->setPos(newPos);
}
