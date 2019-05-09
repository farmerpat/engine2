#include "include/matrix_of_sprites.hpp"
#include <iostream>
#include <fstream>

MatrixOfSprites::MatrixOfSprites
  (RealPoint pos, int w, int h, int nRows, int nCols, int xPad, int yPad, int xScale, int yScale, std::string img, SDL_Renderer *r)
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

  for (int i=0; i<this->_numRows; i++) {
    for (int j=0; j<this->_numCols; j++) {
      int &val = this->_matrix[i][j];

      if (val == 1) {

        std::cout <<"fyf\n";
      } else {
        std::cout << "no es fyf\n";
      }
    }
  }

  //for (auto &row : this->_matrix) {
    //for (auto &value : row) {
      //if (value == 1) {
        //std::cout <<"fyf alot\n";
      //} else {
        //std::cout << "no es fyf\n";
      //}
    //}
  //}

  // store an array (vector?) of 1s that will be zeroed when they are not to be displayed
  //this->_matrix = (char*)malloc(sizeof(char)*nRows*nCols);
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
    x = xBase + (i * (this->_width + this->_xPad));

    for (int j=0; j<this->_numCols; j++) {
      y = yBase + (j * (this->_height + this->_yPad));
      texture_dest_rect.x = x;
      texture_dest_rect.y = y;
      texture_dest_rect.w = this->getWidth() * this->_xScale;
      texture_dest_rect.h = this->getHeight() * this->_yScale;

      SDL_RenderCopy(renderer, this->_texture, NULL, &texture_dest_rect);

    }
  }
}

void MatrixOfSprites::collisionHandler(std::unique_ptr<Sprite> &other) {
}

bool MatrixOfSprites::isCollidingWith(std::unique_ptr<Sprite> &other) {
  return false;
}
