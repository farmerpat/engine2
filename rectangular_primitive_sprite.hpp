#ifndef RECTANGULAR_PRIMITIVE_SPRITE_HPP
#define RECTANGULAR_PRIMITIVE_SPRITE_HPP

#include "primitive_sprite.hpp"

class RectangularPrimitiveSprite : public PrimitiveSprite {
  public:
    RectangularPrimitiveSprite(RealPoint);
    RectangularPrimitiveSprite(RealPoint, int, int);
    RectangularPrimitiveSprite(RealPoint, int, int, SDL_Color);
    void render(SDL_Renderer*);
    void setFilled();
    void clearFilled();

  protected:
    int _width;
    int _height;
    bool _filled = false;

};

#endif
