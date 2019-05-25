#include "include/piece_controller.hpp"
#include "include/piece.hpp"

PieceController::PieceController(Piece *p) {
  this->_piece = p;
}

void PieceController::update(float dt) {
  this->_gravityFrameCounter++;
  GameManager *gm = GameManager::getInstance();
  int move = 0;
  bool downAccel = false;

  RealPoint newPos(
    this->_piece->getPos()->X(),
    this->_piece->getPos()->Y()
  );

  if (gm) {
    if (gm->playerInput.bPressed) {
      // then the d-pad should warp the piece, not move it
      if (gm->playerInput.leftJustPressed) {
        this->_piece->distortLeft();
      } else if (gm->playerInput.rightJustPressed) {
        this->_piece->distortRight();
      } else if (gm->playerInput.upJustPressed) {
        this->_piece->distortUp();
      } else if (gm->playerInput.downJustPressed) {
        this->_piece->distortDown();
      }
    } else {
      if (gm->playerInput.leftJustPressed) {
        // keep it in bounds
        move = -this->_moveSize;

      } else if (gm->playerInput.rightJustPressed) {
        move = this->_moveSize;

      }

      if (gm->playerInput.downHeld) {
        downAccel = true;
      }
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
            bool allowFlip = true;

            for (int i=0; i<3; i++) {
              if (!allowFlip) break;
              for (int j=0; j<3; j++) {
                // i have no idea why these are backwards
                // figure out a way to optionally make sure that all the blocks can be flipped
                // before flipping any
                if (this->_piece->getBitAt(j,i) == 1) {
                  if (!bgMat->getBitAt(pieceMatrixPositionY+j, pieceMatrixPositionX+i) == 0) {
                    allowFlip = false;
                    break;

                  }
                }
              }
            }

            if (allowFlip) {
              for (int i=0; i<3; i++) {
                for (int j=0; j<3; j++) {
                  if (this->_piece->getBitAt(j,i) == 1) {
                    // tell it to flip the hole bit somehow
                    pl->setBgHoleBit(pieceMatrixPositionX, pieceMatrixPositionY, i, j, 1);
                    bgMat->setBitAt(pieceMatrixPositionY+j,pieceMatrixPositionX+i,1);
                    this->_piece->setBitAt(j,i,0);

                  }
                }
              }
            }

            /*
             if (bgMat->getBitAt(pieceMatrixPositionY+j, pieceMatrixPositionX+i) == 0) {
               if (this->_piece->getBitAt(j,i) == 1) {
                 bgMat->setBitAt(pieceMatrixPositionY+j,pieceMatrixPositionX+i,1);
                 this->_piece->setBitAt(j,i,0);

               }
             }
           */

          }
        }
      }
    } else if (gm->playerInput.xJustPressed) {
      this->_piece->rotateCounterClockwise();
    } else if (gm->playerInput.yJustPressed) {
      this->_piece->rotateClockwise();
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
  } else {
    if (downAccel) {
      this->_gravityFrameCounter += 50;
    }
  }

  if (!this->_piece->someBlockSet()) {
    this->_piece->kill();
  }

  this->_piece->setPos(newPos);
}
