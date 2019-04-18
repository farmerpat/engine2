#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include "SDL.h"

class Path {
  public:
    Path();
    ~Path();
    void addNode(SDL_Point);
    void advance();
    void rewind();
    SDL_Point *getCurrentPoint();

  protected:
    int _current = 0;
    std::vector<SDL_Point*> _nodes;

};
#endif
