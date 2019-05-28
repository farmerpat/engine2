#include "include/o_piece.hpp"

ScreenMatrix OPiece::_map(3, 3, 1);
// why fail?
//OPiece::_map.setBitAt(1, 1, 0);

OPiece::OPiece(RealPoint pos, SDL_Renderer *renderer)
  : Piece (pos, "assets/pink_block.png", renderer, OPiece::_map) {
  this->_blockWidth = 16;
  this->_blockMap.setBitAt(1,1,0);
}

void OPiece::rotateClockwise() {
  ScreenMatrix tempBlockMap(3, 3, 0);
  tempBlockMap.setBitAt(0,0, this->_blockMap.getBitAt(2,0));
  tempBlockMap.setBitAt(0,1, this->_blockMap.getBitAt(1,0));
  tempBlockMap.setBitAt(0,2, this->_blockMap.getBitAt(0,0));
  tempBlockMap.setBitAt(1,0, this->_blockMap.getBitAt(2,1));
  tempBlockMap.setBitAt(1,1, this->_blockMap.getBitAt(1,1));
  tempBlockMap.setBitAt(1,2, this->_blockMap.getBitAt(0,1));
  tempBlockMap.setBitAt(2,0, this->_blockMap.getBitAt(2,2));
  tempBlockMap.setBitAt(2,1, this->_blockMap.getBitAt(1,2));
  tempBlockMap.setBitAt(2,2, this->_blockMap.getBitAt(0,2));

  this->_blockMap = tempBlockMap;
}

void OPiece::rotateCounterClockwise() {
  ScreenMatrix tempBlockMap(3, 3, 0);
  tempBlockMap.setBitAt(0,0, this->_blockMap.getBitAt(0,2));
  tempBlockMap.setBitAt(0,1, this->_blockMap.getBitAt(1,2));
  tempBlockMap.setBitAt(0,2, this->_blockMap.getBitAt(2,2));
  tempBlockMap.setBitAt(1,0, this->_blockMap.getBitAt(0,1));
  tempBlockMap.setBitAt(1,1, this->_blockMap.getBitAt(1,1));
  tempBlockMap.setBitAt(1,2, this->_blockMap.getBitAt(2,1));
  tempBlockMap.setBitAt(2,0, this->_blockMap.getBitAt(0,0));
  tempBlockMap.setBitAt(2,1, this->_blockMap.getBitAt(1,0));
  tempBlockMap.setBitAt(2,2, this->_blockMap.getBitAt(2,0));

  this->_blockMap = tempBlockMap;
}

// TODO: if i only end up implementing shrinking a piece, these
// will be the same for all the pieces. if so move them back to Piece.
void OPiece::distortLeft() {
  if (this->_blockMap.getBitAt(2,0) || this->_blockMap.getBitAt(2,1) || this->_blockMap.getBitAt(2,2)) {
    this->_blockMap.setBitAt(1,0,this->_blockMap.getBitAt(2,0));
    this->_blockMap.setBitAt(1,1,this->_blockMap.getBitAt(2,1));
    this->_blockMap.setBitAt(1,2,this->_blockMap.getBitAt(2,2));
    this->_blockMap.setBitAt(2,0,0);
    this->_blockMap.setBitAt(2,1,0);
    this->_blockMap.setBitAt(2,2,0);

  } else if (this->_blockMap.getBitAt(1,0) || this->_blockMap.getBitAt(1,1) || this->_blockMap.getBitAt(1,2)) {
    this->_blockMap.setBitAt(0,0,this->_blockMap.getBitAt(1,0));
    this->_blockMap.setBitAt(0,1,this->_blockMap.getBitAt(1,1));
    this->_blockMap.setBitAt(0,2,this->_blockMap.getBitAt(1,2));
    this->_blockMap.setBitAt(1,0,0);
    this->_blockMap.setBitAt(1,1,0);
    this->_blockMap.setBitAt(1,2,0);

  }
}

void OPiece::distortRight() {
  if (this->_blockMap.getBitAt(0,0) || this->_blockMap.getBitAt(0,1) || this->_blockMap.getBitAt(0,2)) {
    this->_blockMap.setBitAt(1,0,this->_blockMap.getBitAt(0,0));
    this->_blockMap.setBitAt(1,1,this->_blockMap.getBitAt(0,1));
    this->_blockMap.setBitAt(1,2,this->_blockMap.getBitAt(0,2));
    this->_blockMap.setBitAt(0,0,0);
    this->_blockMap.setBitAt(0,1,0);
    this->_blockMap.setBitAt(0,2,0);

  } else if (this->_blockMap.getBitAt(1,0) || this->_blockMap.getBitAt(1,1) || this->_blockMap.getBitAt(1,2)) {
    this->_blockMap.setBitAt(2,0,this->_blockMap.getBitAt(1,0));
    this->_blockMap.setBitAt(2,1,this->_blockMap.getBitAt(1,1));
    this->_blockMap.setBitAt(2,2,this->_blockMap.getBitAt(1,2));
    this->_blockMap.setBitAt(1,0,0);
    this->_blockMap.setBitAt(1,1,0);
    this->_blockMap.setBitAt(1,2,0);

  }
}

void OPiece::distortUp() {
  if (this->_blockMap.getBitAt(0,2) || this->_blockMap.getBitAt(1,2) || this->_blockMap.getBitAt(2,2)) {
    this->_blockMap.setBitAt(0,1, this->_blockMap.getBitAt(0,2));
    this->_blockMap.setBitAt(1,1, this->_blockMap.getBitAt(1,2));
    this->_blockMap.setBitAt(2,1, this->_blockMap.getBitAt(2,2));
    this->_blockMap.setBitAt(0,2,0);
    this->_blockMap.setBitAt(1,2,0);
    this->_blockMap.setBitAt(2,2,0);

  } else if (this->_blockMap.getBitAt(0,1) || this->_blockMap.getBitAt(1,1) || this->_blockMap.getBitAt(2,1)) {
    this->_blockMap.setBitAt(0,0, this->_blockMap.getBitAt(0,1));
    this->_blockMap.setBitAt(1,0, this->_blockMap.getBitAt(1,1));
    this->_blockMap.setBitAt(2,0, this->_blockMap.getBitAt(2,1));
    this->_blockMap.setBitAt(0,1,0);
    this->_blockMap.setBitAt(1,1,0);
    this->_blockMap.setBitAt(2,1,0);

  }
}

void OPiece::distortDown() {
  if (this->_blockMap.getBitAt(0,0) || this->_blockMap.getBitAt(1,0) || this->_blockMap.getBitAt(2,0)) {
    this->_blockMap.setBitAt(0,1,this->_blockMap.getBitAt(0,0));
    this->_blockMap.setBitAt(1,1,this->_blockMap.getBitAt(1,0));
    this->_blockMap.setBitAt(2,1,this->_blockMap.getBitAt(2,0));
    this->_blockMap.setBitAt(0,0,0);
    this->_blockMap.setBitAt(1,0,0);
    this->_blockMap.setBitAt(2,0,0);

  } else if (this->_blockMap.getBitAt(0,1) || this->_blockMap.getBitAt(1,1) || this->_blockMap.getBitAt(2,1)) {
    this->_blockMap.setBitAt(0,2,this->_blockMap.getBitAt(0,1));
    this->_blockMap.setBitAt(1,2,this->_blockMap.getBitAt(1,1));
    this->_blockMap.setBitAt(2,2,this->_blockMap.getBitAt(2,1));
    this->_blockMap.setBitAt(0,1,0);
    this->_blockMap.setBitAt(1,1,0);
    this->_blockMap.setBitAt(2,1,0);

  }
}
