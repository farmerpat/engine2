#ifndef REAL_POINT_HPP
#define REAL_POINT_HPP

#include "SDL.h"

class RealPoint {
  public:
    RealPoint();
    RealPoint(float, float);
    float X() const;
    float Y() const;
    void setX(float);
    void setY(float);
    SDL_Point *toSdlPoint();

  protected:
    float _x;
    float _y;
};
#endif
