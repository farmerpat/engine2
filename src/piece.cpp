#include "include/piece.hpp"

Piece::Piece(RealPoint pos, std::string file, SDL_Renderer *renderer, ScreenMatrix map)
  : Sprite(pos) {
    this->_width = this->_blockWidth * this->_numCols;
    this->_height = this->_blockWidth * this->_numRows;
    this->_blockTexture = Util::loadTexture(file, renderer);
    this->_controller = new PieceController(this);
    this->_tag = "puzzle_piece";
    this->_blockMap = map;
}

Piece::Piece(RealPoint pos, std::string file, SDL_Renderer *renderer)
  : Sprite(pos) {
    this->_width = this->_blockWidth * this->_numCols;
    this->_height = this->_blockWidth * this->_numRows;
    this->_blockTexture = Util::loadTexture(file, renderer);
    this->_controller = new PieceController(this);
    this->_tag = "puzzle_piece";

    ScreenMatrix mat(3, 3, 1);
    this->_blockMap = mat;
}

Piece::~Piece() {
  if (this->_blockTexture) {
    SDL_DestroyTexture(this->_blockTexture);
  }
}

void Piece::render(SDL_Renderer* renderer) {
  // put the texture everywhere we have a 1 on the map
  RealPoint thisBlockPos;
  SDL_Rect textureDestRect;
  int thisXOffset;
  int thisYOffset;

  for (char y=0; y<this->_numRows; y++) {
    thisYOffset = y * this->_blockWidth;
    thisBlockPos.setY(this->_pos->Y() + thisYOffset);

    for (char x=0; x<this->_numCols; x++) {
      thisXOffset = x * this->_blockWidth;
      thisBlockPos.setX(this->_pos->X() + thisXOffset);

      if (this->_blockMap.getBitAt(x, y)) {
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

ScreenMatrix Piece::getMatrix () { return this->_blockMap; }

bool Piece::someBlockSet() {
  bool pred = false;

  for (int y=0; y<this->_numRows; y++) {
    for (int x=0; x<this->_numCols; x++) {
      if (this->_blockMap.getBitAt(x,y) != 0) {
        pred = true;
        break;

      }
    }
  }

  return pred;
}
