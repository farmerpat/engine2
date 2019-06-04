#include "include/screen_matrix.hpp"

ScreenMatrix::ScreenMatrix() { }
// rows is y
// cols is x
ScreenMatrix::ScreenMatrix(int xMax, int yMax, int fill=0) {
  this->_xMax = xMax;
  this->_yMax = yMax;

  for (int x=0; x<this->_xMax; x++) {
    std::vector<int> row;

    for (int y=0; y<this->_yMax; y++) {
      row.push_back(fill);
    }

    this->_mat.push_back(row);
  }
}

ScreenMatrix::~ScreenMatrix() {
  this->_mat.clear();
}

void ScreenMatrix::setBitAt(int x, int y, int val) {
  this->_mat[x][y] = val;
}

int ScreenMatrix::getBitAt(int x, int y) {
  return this->_mat[x][y];
}

void ScreenMatrix::print() {
  for (int y=0; y<this->_yMax; y++) {
    for (int x=0; x<this->_xMax; x++) {
      std::cout << this->_mat[x][y];
    }
  }
}

bool ScreenMatrix::someEmptyBlocks() {
  bool pred = false;

  for (int y=0; y<this->_yMax; y++) {
    if (pred) break;
    for (int x=0; x<this->_xMax; x++) {
      if (this->_mat[x][y] == 0) {
        pred = true;
        break;

      }
    }
  }

  return pred;
}

int ScreenMatrix::getLastNonEmptyColumnIndex() {
  int index = -1;

  for (int x=this->_xMax-1; x>-1; x--) {
    bool someOnes = false;
    for (int y=0; y<this->_yMax; y++) {
      if (this->_mat[x][y]) {
        someOnes = true;
        break;

      }
    }

    if (someOnes) {
      index = x;
      break;
    }
  }

  return index;
}

int ScreenMatrix::getFirstNonEmptyColumnIndex() {
  int index = -1;
  for (int x=0; x<this->_xMax; x++) {
    bool someOnes = false;

    for (int y=0; y<this->_yMax; y++) {
      if (this->_mat[x][y]) {
        someOnes = true;
        break;
      }
    }

    if (someOnes) {
      index = x;
      break;
    }
  }

  return index;
}

