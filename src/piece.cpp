#include "include/piece.hpp"

Piece::Piece(RealPoint pos, std::string file, SDL_Renderer *renderer)
  : Sprite(pos) {
    this->_width = this->_blockWidth * this->_numCols;
    this->_height = this->_blockWidth * this->_numRows;
    this->_blockTexture = Util::loadTexture(file, renderer);
}

Piece::~Piece() {
  if (this->_blockTexture) {
    SDL_DestroyTexture(this->_blockTexture);
  }
}

void Piece::rotateClockwise() {

}

void Piece::rotateCounterClockwise() {

}

void Piece::render(SDL_Renderer* renderer) {
  // put the texture everywhere we have a 1 on the map
  RealPoint thisBlockPos;
  SDL_Rect textureDestRect;
  int thisXOffset;
  int thisYOffset;

  for (char i=0; i<this->_numRows; i++) {
    thisYOffset = i * this->_blockWidth;
    thisBlockPos.setY(this->_pos->Y() + thisYOffset);

    for (char j=0; j<this->_numCols; j++) {
      thisXOffset = j * this->_blockWidth;
      thisBlockPos.setX(this->_pos->X() + thisXOffset);

      if (this->_blockMap[i][j]) {
        // then render it
        textureDestRect.x = (int)thisBlockPos.X();
        textureDestRect.y = (int)thisBlockPos.Y();
        textureDestRect.w = this->_blockWidth * this->_xScale;
        textureDestRect.h = this->_blockWidth * this->_yScale;

        SDL_RenderCopy(renderer, this->_blockTexture, NULL, &textureDestRect);

      }
    }
  }
}

void Piece::update(float dt) { }
