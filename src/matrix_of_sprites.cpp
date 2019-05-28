#include "include/matrix_of_sprites.hpp"
#include <iostream>

MatrixOfSprites::MatrixOfSprites
  (RealPoint pos, int w, int h, int nRows, int nCols, int xPad, int yPad, int xScale, int yScale, std::string img, SDL_Renderer *r, ScreenMatrix map)
  : Sprite (pos, w, h) {

  this->_numRows = nRows;
  this->_numCols = nCols;
  this->_xPad = xPad;
  this->_yPad = yPad;
  this->_texture = Util::loadTexture(img, r);
  this->setXScale(xScale);
  this->setYScale(yScale);
  this->_isAggregate = true;
  this->setLayer(1);

  this->_matrix = map;
}

// ROWS IS YMAX
// COLS IS XMAX
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
  this->_isAggregate = true;
  this->setLayer(1);

  ScreenMatrix mat(nCols, nRows, 1);
  this->_matrix = mat;

}

/*
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
  this->_isAggregate = true;
  this->setLayer(1);

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
*/

MatrixOfSprites::~MatrixOfSprites() {
  if (this->_texture) {
    SDL_DestroyTexture(this->_texture);
  }

  //for (auto row : this->_matrix) {
    //row.clear();
  //}

  //this->_matrix.clear();
}

void MatrixOfSprites::render(SDL_Renderer *renderer) {
  SDL_Rect texture_dest_rect;
  int xBase = (int)this->getPos()->X();
  int yBase = (int)this->getPos()->Y();
  int rectX;
  int rectY;

  // probably just grab maxX from _mat
  for (int y=0; y<this->_numRows; y++) {
    rectY = yBase + (y * (this->_width + this->_yPad));

    for (int x=0; x<this->_numCols; x++) {
      if (this->_matrix.getBitAt(x, y)) {
        rectX = xBase + (x * (this->_width + this->_xPad));
        texture_dest_rect.x = rectX;
        texture_dest_rect.y = rectY;
        texture_dest_rect.w = this->getWidth() * this->_xScale;
        texture_dest_rect.h = this->getHeight() * this->_yScale;

        SDL_RenderCopy(renderer, this->_texture, NULL, &texture_dest_rect);
      }
    }
  }
}

// TODO: this seems so specific to invaderz that making collisionHandler
// an object probably makes more sense.
// TODO: update to use ScreenMatrix
void MatrixOfSprites::collisionHandler(std::unique_ptr<Sprite> &other) {
  /*
  SDL_Rect theirHitBox = other->getGlobalHitBox();
  SDL_Rect myHitBox;
  int xBase = (int)this->getPos()->X();
  int yBase = (int)this->getPos()->Y();
  int x;
  int y;
  int height = this->_height;
  int width = this->_width;
  int xPad = this->_xPad;
  int yPad = this->_yPad;
  int xScale = this->_xScale;
  int yScale = this->_yScale;

  for (int i=0; i<this->_numRows; i++) {
    y = yBase + (i * (this->_width + this->_yPad));
    myHitBox.y = y;

    for (int j=0; j<this->_numCols; j++) {
      if (this->_matrix[i][j]) {
        x = xBase + (j * (width + xPad));
        myHitBox.x = x;
        myHitBox.w = width * xScale;
        myHitBox.h = height * yScale;

        if (SDL_HasIntersection(&myHitBox, &theirHitBox)) {
          if (other->getTag() == "player_bullet") {
            this->_matrix[i][j] = 0;
            other->kill();

          }
        }
      }
    }
  }
  */
}

// TODO: update to use ScreenMatrix
bool MatrixOfSprites::isCollidingWith(std::unique_ptr<Sprite> &other) {
  /*
  // TODO: this could be more effecient. should be able to limit
  // i/j max based on other's hitbox. similarly for collisionHandler
  // furthermore, this is the same shape as collisionHandler. factor this out
  SDL_Rect theirHitBox = other->getGlobalHitBox();
  SDL_Rect myHitBox;
  int xBase = (int)this->getPos()->X();
  int yBase = (int)this->getPos()->Y();
  int x;
  int y;
  int height = this->_height;
  int width = this->_width;
  int xPad = this->_xPad;
  int yPad = this->_yPad;
  int xScale = this->_xScale;
  int yScale = this->_yScale;

  for (int i=0; i<this->_numRows; i++) {
    y = yBase + (i * (this->_width + this->_yPad));
    myHitBox.y = y;

    for (int j=0; j<this->_numCols; j++) {
      if (this->_matrix[i][j]) {
        x = xBase + (j * (width + xPad));
        myHitBox.x = x;
        myHitBox.w = width * xScale;
        myHitBox.h = height * yScale;

        if (SDL_HasIntersection(&myHitBox, &theirHitBox)) {
          return true;

        }
      }
    }
  }
  */

  return false;
}

int MatrixOfSprites::getXPad() {
  return this->_xPad;
}

int MatrixOfSprites::getYPad() {
  return this->_yPad;
}

int MatrixOfSprites::getNumCols() {
  return this->_numCols;
}

int MatrixOfSprites::getNumRows() {
  return this->_numRows;
}

//ScreenMatrix const MatrixOfSprites::getMatrix() const {
  //return this->_matrix;
//}

ScreenMatrix& MatrixOfSprites::getMatrix() {
  return this->_matrix;
}

// TODO:
// optimize this. e.g. can isCollidingWith use this?
SDL_Rect MatrixOfSprites::getHitBoxAt(int row, int col) {
  SDL_Rect hb;

  int height = this->_height;
  int width = this->_width;
  int xPad = this->_xPad;
  int yPad = this->_yPad;
  int xScale = this->_xScale;
  int yScale = this->_yScale;

  int yBase = (int)this->getPos()->Y();
  int xBase = (int)this->getPos()->X();
  int y = yBase + (row * (height + yPad));
  int x = xBase + (col * (width + xPad));

  hb.y = y;
  hb.x = x;
  hb.w = width * xScale;
  hb.h = height * yScale;

  return hb;
}

//int MatrixOfSprites::getBitAt(int x,int y) {
  //return this->_matrix[x][y];
//}

//void MatrixOfSprites::setBitAt(int x ,int y ,int val) {
  //this->_matrix[x][y] = val;
//}
