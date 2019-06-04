#include "include/piece_controller.hpp"
#include "include/piece.hpp"
#include <iostream>

PieceController::PieceController(Piece *p) {
  this->_piece = p;
}

void PieceController::update(float dt) {
  this->_gravityFrameCounter++;
  GameManager *gm = GameManager::getInstance();
  int moveX = 0;
  int moveY = 0;
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
        moveX = -this->_moveSize;

      } else if (gm->playerInput.rightJustPressed) {
        moveX = this->_moveSize;

      } else if (gm->playerInput.downJustPressed) {
        moveY = this->_moveSize;

      } else if (gm->playerInput.upJustPressed) {
        moveY = -this->_moveSize;

      } else if (gm->playerInput.downHeld) {
        //downAccel = true;
        //moveY = 2 * this->_moveSize;
        moveY = this->_moveSize;

      } else if (gm->playerInput.upHeld) {
        //moveY = 2 * -this->_moveSize;
        moveY = -this->_moveSize;

      } else if (gm->playerInput.leftHeld) {
        //moveX = 2 * -this->_moveSize;
        moveX = -this->_moveSize;

      } else if (gm->playerInput.rightHeld) {
        //moveX = 2 * this->_moveSize;
        moveX = this->_moveSize;

      }
    }

    if (gm->playerInput.aJustPressed) {
      Level *l = gm->getCurrentLevel();
      if (l) {
        PuzzleLevel *pl = static_cast<PuzzleLevel*>(l);

        if (pl) {
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
          // this will have to be expanded to all for holes that are partially on screen
          if (pieceMatrixPositionX >=0 && pieceMatrixPositionY>=0) {
            pieceMatrixPositionX /= cellWidth;
            pieceMatrixPositionY /= cellHeight;

            // at present, there are 3 rows and 3 cols in a piece.
            // this could be updated to be more flexible
            bool allowFlip = true;

            for (int y=0; y<3; y++) {
              if (!allowFlip) break;
              for (int x=0; x<3; x++) {
                // figure out a way to optionally make sure that all the blocks can be flipped
                // before flipping any
                if (this->_piece->getMatrix().getBitAt(x, y) == 1) {
                  if (!bgMat->getMatrix().getBitAt(pieceMatrixPositionX+x, pieceMatrixPositionY+y) == 0) {
                    allowFlip = false;
                    break;

                  }
                }
              }
            }

            if (allowFlip) {
              for (int y=0; y<3; y++) {
                for (int x=0; x<3; x++) {
                  if (this->_piece->getMatrix().getBitAt(x,y) == 1) {
                    // tell it to flip the hole bit somehow
                    pl->setBgHoleBit(pieceMatrixPositionX, pieceMatrixPositionY, y, x, 1);
                    this->_piece->getMatrix().setBitAt(x,y,0);

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
  // do it!

  int minXPossible = gm->getIntFromDictionary("screenMatrixMinX");
  int maxXPossible = gm->getIntFromDictionary("screenMatrixMaxX");
  //int maxXPossible = gm->getIntFromDictionary("screenMatrixMaxX") - (this->_piece->);
  int minYPossible = gm->getIntFromDictionary("screenMatrixMinY");
  //int maxYPossible = gm->getIntFromDictionary("screenMatrixMaxY") - (this->_piece->);
  int maxYPossible = gm->getIntFromDictionary("screenMatrixMaxY");

  if ((newPos.X()+moveX) < minXPossible) {
    newPos.setX(minXPossible);
    // actually caculate based on the piece size
  } else if ((newPos.X()+moveX) > (maxXPossible-16*3)) {
    newPos.setX(maxXPossible-16*3);
  } else {
    newPos.setX(newPos.X()+moveX);
  }

  if ((newPos.Y()+moveY) < minYPossible) {
    newPos.setY(minYPossible);
    // TDOO: pull these from piece or something...magick #s bad!
  } else if ((newPos.Y()+moveY) > (maxYPossible-16*3)) {
    newPos.setY(maxYPossible-16*3);
  } else {
    newPos.setY(newPos.Y()+moveY);
  }

  if (this->_gravityFrameCounter >= this->_gravityFrameDelay) {
    this->_gravityFrameCounter = 0;
    //newPos.setY(newPos.Y()+this->_gravity);

    // TODO:
    // this is no good. must prevent moves that would take us OOB.
    if (newPos.Y() >= (gm->getScreenHeight()-(this->_piece->getBlockWidth() * this->_piece->getMatrix().getYMax()) )) {
      //this->_piece->kill();
      newPos.setY(gm->getScreenHeight() - (this->_piece->getBlockWidth() * this->_piece->getMatrix().getYMax()));
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
