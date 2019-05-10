#include "include/matrix_of_sprites.hpp"
#include <iostream>
#include <fstream>

MatrixOfSprites::MatrixOfSprites
  (RealPoint pos, int w, int h, int nRows, int nCols, int xPad, int yPad, int xScale, int yScale, std::string img, SDL_Renderer *r, int **map = 0)
  : Sprite (pos, w, h) {

  this->_numRows = nRows;
  this->_numCols = nCols;
  this->_xPad = xPad;
  this->_yPad = yPad;
  this->_texture = Util::loadTexture(img, r);
  this->setXScale(xScale);
  this->setYScale(yScale);

  for (int i=0; i<this->_numRows; i++) {
    this->_matrix.push_back(std::vector<int>(this->_numCols, 1));
  }

  if (map) {
    for (int i=0; i<this->_numRows; i++) {
      for (int j=0; j<this->_numCols; j++) {
        this->_matrix[i][j] = *(*(map+i)+j);

      }
    }
  }
}

MatrixOfSprites::~MatrixOfSprites() {
  if (this->_texture) {
    SDL_DestroyTexture(this->_texture);
  }

  for (auto row : this->_matrix) {
    row.clear();
  }

  this->_matrix.clear();
}

void MatrixOfSprites::render(SDL_Renderer *renderer) {
  SDL_Rect texture_dest_rect;
  int xBase = (int)this->getPos()->X();
  int yBase = (int)this->getPos()->Y();
  int x;
  int y;

  for (int i=0; i<this->_numRows; i++) {
    y = yBase + (i * (this->_width + this->_yPad));

    for (int j=0; j<this->_numCols; j++) {
      if (this->_matrix[i][j]) {
        x = xBase + (j * (this->_height + this->_xPad));
        texture_dest_rect.x = x;
        texture_dest_rect.y = y;
        texture_dest_rect.w = this->getWidth() * this->_xScale;
        texture_dest_rect.h = this->getHeight() * this->_yScale;

        SDL_RenderCopy(renderer, this->_texture, NULL, &texture_dest_rect);
      }
    }
  }
}

void MatrixOfSprites::collisionHandler(std::unique_ptr<Sprite> &other) {
}

bool MatrixOfSprites::isCollidingWith(std::unique_ptr<Sprite> &other) {
  return false;
}
