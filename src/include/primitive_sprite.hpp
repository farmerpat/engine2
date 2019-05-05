#ifndef PRIMITIVE_SPRITE_HPP
#define PRIMITIVE_SPRITE_HPP

#include "sprite.hpp"

class PrimitiveSprite : public Sprite {
  public:
    PrimitiveSprite (RealPoint);
    ~PrimitiveSprite();
    void render(SDL_Renderer*);

  protected:
    SDL_Color *_fillColor = 0;
    SDL_Color *_outlineColor = 0;

};
#endif
