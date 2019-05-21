#include "include/o_piece.hpp"

const std::vector<std::vector<int>> OPiece::_map = { {1,1,1}, {1,0,1}, {1,1,1} };

OPiece::OPiece(RealPoint pos, SDL_Renderer *renderer)
  : Piece (pos, "assets/pink_block.png", renderer, OPiece::_map) { }

//OPiece::OPiece(RealPoint pos, std::string file, SDL_Renderer *renderer)
  //: Piece (pos, file, renderer, OPiece::_map) { }

void OPiece::rotateClockwise() {
  std::vector<std::vector<int>> tempBlockMap = { {0,0,0}, {0,0,0}, {0,0,0} };
  tempBlockMap[0][0] = this->_blockMap[2][0];
  tempBlockMap[0][1] = this->_blockMap[1][0];
  tempBlockMap[0][2] = this->_blockMap[0][0];
  tempBlockMap[1][0] = this->_blockMap[2][1];
  tempBlockMap[1][1] = this->_blockMap[1][1];
  tempBlockMap[1][2] = this->_blockMap[0][1];
  tempBlockMap[2][0] = this->_blockMap[2][2];
  tempBlockMap[2][1] = this->_blockMap[1][2];
  tempBlockMap[2][2] = this->_blockMap[0][2];

  this->_blockMap = tempBlockMap;
}

void OPiece::rotateCounterClockwise() {
  std::vector<std::vector<int>> tempBlockMap = { {0,0,0}, {0,0,0}, {0,0,0} };

  tempBlockMap[0][0] = this->_blockMap[0][2];
  tempBlockMap[0][1] = this->_blockMap[1][2];
  tempBlockMap[0][2] = this->_blockMap[2][2];
  tempBlockMap[1][0] = this->_blockMap[0][1];
  tempBlockMap[1][1] = this->_blockMap[1][1];
  tempBlockMap[1][2] = this->_blockMap[2][1];
  tempBlockMap[2][0] = this->_blockMap[0][0];
  tempBlockMap[2][1] = this->_blockMap[1][0];
  tempBlockMap[2][2] = this->_blockMap[2][0];
  this->_blockMap = tempBlockMap;
}

// TODO: if i only end up implementing shrinking a piece, these
// will be the same for all the pieces. if so move them back to Piece.
void OPiece::distortLeft() {
  if (this->_blockMap[0][2] || this->_blockMap[1][2] || this->_blockMap[2][2]) {
    this->_blockMap[0][1] = this->_blockMap[0][2];
    this->_blockMap[1][1] = this->_blockMap[1][2];
    this->_blockMap[2][1] = this->_blockMap[2][2];
    this->_blockMap[0][2] = 0;
    this->_blockMap[1][2] = 0;
    this->_blockMap[2][2] = 0;

  } else if (this->_blockMap[0][1] || this->_blockMap[1][1] || this->_blockMap[2][1]) {
    this->_blockMap[0][0] = this->_blockMap[0][1];
    this->_blockMap[1][0] = this->_blockMap[1][1];
    this->_blockMap[2][0] = this->_blockMap[2][1];
    this->_blockMap[0][1] = 0;
    this->_blockMap[1][1] = 0;
    this->_blockMap[2][1] = 0;

  }
}

void OPiece::distortRight() {
  if (this->_blockMap[0][0] || this->_blockMap[1][0] || this->_blockMap[2][0]) {
    this->_blockMap[0][1] = this->_blockMap[0][0];
    this->_blockMap[1][1] = this->_blockMap[1][0];
    this->_blockMap[2][1] = this->_blockMap[2][0];
    this->_blockMap[0][0] = 0;
    this->_blockMap[1][0] = 0;
    this->_blockMap[2][0] = 0;

  } else if (this->_blockMap[0][1] || this->_blockMap[1][1] || this->_blockMap[2][1]) {
    this->_blockMap[0][2] = this->_blockMap[0][1];
    this->_blockMap[1][2] = this->_blockMap[1][1];
    this->_blockMap[2][2] = this->_blockMap[2][1];
    this->_blockMap[0][1] = 0;
    this->_blockMap[1][1] = 0;
    this->_blockMap[2][1] = 0;

  }
}

void OPiece::distortUp() {
  if (this->_blockMap[2][0] || this->_blockMap[2][1] || this->_blockMap[2][2]) {
    this->_blockMap[1][0] = this->_blockMap[2][0];
    this->_blockMap[1][1] = this->_blockMap[2][1];
    this->_blockMap[1][2] = this->_blockMap[2][2];
    this->_blockMap[2][0] = 0;
    this->_blockMap[2][1] = 0;
    this->_blockMap[2][2] = 0;

  } else if (this->_blockMap[1][0] || this->_blockMap[1][1] || this->_blockMap[1][2]) {
    this->_blockMap[0][0] = this->_blockMap[1][0];
    this->_blockMap[0][1] = this->_blockMap[1][1];
    this->_blockMap[0][2] = this->_blockMap[1][2];
    this->_blockMap[1][0] = 0;
    this->_blockMap[1][1] = 0;
    this->_blockMap[1][2] = 0;

  }
}

void OPiece::distortDown() {
  if (this->_blockMap[0][0] || this->_blockMap[0][1] || this->_blockMap[0][2]) {
    this->_blockMap[1][0] = this->_blockMap[0][0];
    this->_blockMap[1][1] = this->_blockMap[0][1];
    this->_blockMap[1][2] = this->_blockMap[0][2];
    this->_blockMap[0][0] = 0;
    this->_blockMap[0][1] = 0;
    this->_blockMap[0][2] = 0;

  } else if (this->_blockMap[1][0] || this->_blockMap[1][1] || this->_blockMap[1][2]) {
    this->_blockMap[2][0] = this->_blockMap[1][0];
    this->_blockMap[2][1] = this->_blockMap[1][1];
    this->_blockMap[2][2] = this->_blockMap[1][2];
    this->_blockMap[1][0] = 0;
    this->_blockMap[1][1] = 0;
    this->_blockMap[1][2] = 0;

  }
}
