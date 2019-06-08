#ifndef SCREEN_MATRIX_HPP
#define SCREEN_MATRIX_HPP

#include <vector>
#include <iostream>

// TODO?
// this could be changed to a template to support other
// types
class ScreenMatrix {
  public:
    ScreenMatrix();
    ScreenMatrix(int,int,int);
    ~ScreenMatrix();
    void setBitAt(int,int,int);
    //int getBitAt(int,int) const;
    int getBitAt(int,int);
    void print();
    int getXMax() { return this->_xMax; }
    int getYMax() { return this->_yMax; }
    bool someEmptyBlocks();
    bool noEmptyBlocks();
    int getLastNonEmptyColumnIndex();
    int getFirstNonEmptyColumnIndex();

  protected:
    std::vector<std::vector<int>> _mat;
    int _xMax = 0;
    int _yMax = 0;
};
#endif
