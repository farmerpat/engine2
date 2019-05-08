#ifndef MATRIX_OF_SPRITES_HPP
#define MATRIX_OF_SPRITES_HPP

#include "SDL.h"
#include "sprite.hpp"
#include "util.hpp"
#include <string>
#include <memory>

class MatrixOfSprites : public Sprite {
  public:
    // _pos, width, height, num_rows, num_cols, x_padding, y_padding,
    MatrixOfSprites(RealPoint, int, int, int, int, int, int, int, int, std::string, SDL_Renderer*);
    virtual ~MatrixOfSprites();
    void render(SDL_Renderer*);
    void collisionHandler(std::unique_ptr<Sprite>&) override;
    bool isCollidingWith(std::unique_ptr<Sprite>&) override;

  protected:
    SDL_Texture *_texture = 0;
    int _spriteWidth = 0;
    int _spriteHeight = 0;
    int _numCols = 0;
    int _numRows = 0;
    int _xPad = 0;
    int _yPad = 0;

};
#endif
