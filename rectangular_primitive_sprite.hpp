#ifndef RECTANGULAR_PRIMITIVE_SPRITE_HPP
#define RECTANGULAR_PRIMITIVE_SPRITE_HPP

#include "primitive_sprite.hpp"

class RectangularPrimitiveSprite : public PrimitiveSprite {
  public:
    RectangularPrimitiveSprite(SDL_Point);
    RectangularPrimitiveSprite(SDL_Point, int, int);
    RectangularPrimitiveSprite(SDL_Point, int, int, SDL_Color);
    void render(SDL_Renderer*);
    void setFilled();
    void clearFilled();

  protected:
    int _width;
    int _height;
    bool _filled = false;

};

#endif
