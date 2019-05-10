#include "include/matrix_of_sprites.hpp"

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
        x = xBase + (j * (this->_width + this->_xPad));
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
}

bool MatrixOfSprites::isCollidingWith(std::unique_ptr<Sprite> &other) {
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

int MatrixOfSprites::getFirstNonEmptyColumnIndex() {
  int index = -1;
  for (int j=0; j<this->_numCols; j++) {
    bool someOnes = false;

    for (int i=0; i<this->_numRows; i++) {
      if (this->_matrix[i][j]) {
        someOnes = true;
        break;
      }
    }

    if (someOnes) {
      index = j;
      break;
    }
  }

  return index;
}

int MatrixOfSprites::getLastNonEmptyColumnIndex() {
  int index = -1;

  for (int j=this->_numCols-1; j>-1; j--) {
    bool someOnes = false;
    for (int i=0; i<this->_numRows; i++) {
      if (this->_matrix[i][j]) {
        someOnes = true;
        break;

      }
    }

    if (someOnes) {
      index = j;
      break;
    }
  }

  return index;
}
