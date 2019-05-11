#include "include/invaderz_matrix.hpp"

InvaderzMatrix::InvaderzMatrix(RealPoint pos, int w, int h, int nRows, int nCols, int xPad, int yPad, int xScale, int yScale, SDL_Renderer *r, int **map = 0)
  : MatrixOfSprites(pos, w, h, nRows, nCols, xPad, yPad, xScale, yScale, "assets/enemy1_single_frame.png", r, map) {

    this->_controller = new InvaderzController(this, 30, 175, 1.0);
    this->_aiController = new InvaderzAiController(this);
}

InvaderzMatrix::~InvaderzMatrix() { }
