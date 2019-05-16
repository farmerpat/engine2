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
      // keep it in bounds
      move = -this->_moveSize;

    } else if (gm->playerInput.rightJustPressed) {
      move = this->_moveSize;

    }

    if (gm->playerInput.aJustPressed) {
      Level *l = gm->getCurrentLevel();
      if (l) {
        PuzzleLevel *pl = static_cast<PuzzleLevel*>(l);

        if (pl) {
          // maybe we don't even care about getting the matrix.
          // maybe we
          //const std::vector<std::vector<int>> bgMat = pl->getBackgroundMatrix();
          RealPoint *spritePos = this->_piece->getPos();
          std::shared_ptr<MatrixOfSprites> bgMat = pl->getBackgroundMatrix();
          int matRows = bgMat->getNumRows();
          int matCols = bgMat->getNumCols();
          int cellWidth = bgMat->getWidth();
          int cellHeight = bgMat->getHeight();
          RealPoint *bgMatPos = bgMat->getPos();
          int relativeXZero = (int)bgMatPos->X();
          int relativeYZero = (int)bgMatPos->Y();
          int pieceMatrixPositionX = (int)spritePos->X() - relativeXZero;
          int pieceMatrixPositionY = (int)spritePos->Y() - relativeYZero;

          // if its inside the bg matrix
          if (pieceMatrixPositionX >=0 && pieceMatrixPositionY>=0) {
            pieceMatrixPositionX /= cellWidth;
            pieceMatrixPositionY /= cellHeight;

            // at present, there are 3 rows and 3 cols in a piece.
            // this could be updated to be more flexible
            for (int i=0; i<3; i++) {
              for (int j=0; j<3; j++) {
                // i have no idea why these are backwards
                if (bgMat->getBitAt(pieceMatrixPositionY+j, pieceMatrixPositionX+i) == 0) {
                  if (this->_piece->getBitAt(j,i) == 1) {
                    bgMat->setBitAt(pieceMatrixPositionY+j,pieceMatrixPositionX+i,1);
                    this->_piece->setBitAt(j,i,0);

                  }
                }
              }
            }
          }
        }
      }
    }
  }

  // TODO:
  // keep this in bounds
  newPos.setX(newPos.X()+move);

  if (this->_gravityFrameCounter >= this->_gravityFrameDelay) {
    this->_gravityFrameCounter = 0;
    newPos.setY(newPos.Y()+this->_gravity);

    if (newPos.Y() > gm->getScreenHeight()) {
      this->_piece->kill();
    }
  }

  this->_piece->setPos(newPos);
}
