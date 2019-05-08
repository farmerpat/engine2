#ifndef MATRIX_OF_SPRITES_HPP
#define MATRIX_OF_SPRITES_HPP

#include "SDL.h"
#include "sprite.hpp"

class MatrixOfSprites : Sprite {
  public:
    MatrixOfSprites(RealPoint, int, int, std::string, SDL_Renderer*);
    virtual ~MatrixOfSprites();
    void render(SDL_Renderer*);
    void update(float);

  protected:
    SDL_Texture *_texture = 0;
    int _spriteWidth = 0;
    int _spriteHeight = 0;

};
#endif
