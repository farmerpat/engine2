#ifndef SCREEN_MATRIX_HPP
#define SCREEN_MATRIX_HPP

#include <vector>
#include <iostream>

// TODO?
// this could be changed to a template to support other
// types
class ScreenMatrix {
  public:
    ScreenMatrix(int,int,int);
    ~ScreenMatrix();
    void setBitAt(int,int,int);
    int getBitAt(int,int);
    void print();
    int getXMax() { return this->_xMax; }
    int getYMax() { return this->_yMax; }

  protected:
    std::vector<std::vector<int>> _mat;
    int _xMax = 0;
    int _yMax = 0;
};
#endif
