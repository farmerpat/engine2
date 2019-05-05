#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include "real_point.hpp"
#include "SDL.h"

class Path {
  public:
    Path();
    ~Path();
    void addNode(RealPoint);
    void advance();
    void rewind();
    RealPoint *getCurrentPoint();

  protected:
    int _current = 0;
    std::vector<RealPoint*> _nodes;

};
#endif
