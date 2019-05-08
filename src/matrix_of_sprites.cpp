#include "include/matrix_of_sprites.hpp"

// _pos, width, height, num_rows, num_cols, x_padding, y_padding,
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
}

MatrixOfSprites::~MatrixOfSprites() {
  if (this->_texture) {
    SDL_DestroyTexture(this->_texture);
  }
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
