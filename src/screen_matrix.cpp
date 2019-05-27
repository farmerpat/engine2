#include "include/screen_matrix.hpp"

// rows is y
// cols is x
ScreenMatrix::ScreenMatrix(int xMax, int yMax, int fill=0) {
  this->_xMax = xMax;
  this->_yMax = yMax;

  for (int y=0; y<this->_yMax; y++) {
    std::vector<int> row;

    for (int x=0; x<this->_xMax; x++) {
      row.push_back(fill);
    }

    this->_mat.push_back(row);
  }
}

ScreenMatrix::~ScreenMatrix() {
  this->_mat.clear();
}

void ScreenMatrix::setBitAt(int x, int y, int val) {
  this->_mat[y][x] = val;
}

int ScreenMatrix::getBitAt(int x, int y) {
  return this->_mat[y][x];
}

void ScreenMatrix::print() {
  for (int y=0; y<this->_yMax; y++) {
    for (int x=0; x<this->_xMax; x++) {
      std::cout << this->_mat[y][x];
    }
  }
}
