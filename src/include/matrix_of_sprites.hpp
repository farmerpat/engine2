#ifndef MATRIX_OF_SPRITES_HPP
#define MATRIX_OF_SPRITES_HPP

#include "SDL.h"
#include "sprite.hpp"
#include "util.hpp"
#include <string>
#include <memory>
#include <vector>

class MatrixOfSprites : public Sprite {
  public:
    MatrixOfSprites(
      RealPoint, int, int, int, int, int, int, int, int,
      std::string, SDL_Renderer*, int**
    );

    MatrixOfSprites(
      RealPoint, int, int, int, int, int, int, int, int,
      std::string, SDL_Renderer*, std::vector<std::vector<int>>
    );

    virtual ~MatrixOfSprites();
    void render(SDL_Renderer*);
    void collisionHandler(std::unique_ptr<Sprite>&) override;
    bool isCollidingWith(std::unique_ptr<Sprite>&) override;
    int getFirstNonEmptyColumnIndex();
    int getLastNonEmptyColumnIndex();
    int getXPad();
    int getYPad();
    int getNumCols();
    int getNumRows();
    int getBitAt(int,int);
    void setBitAt(int,int,int);
    std::vector<std::vector<int>> const getMatrix() const;
    SDL_Rect getHitBoxAt(int, int);
    bool someEmptyBlocks();

  protected:
    SDL_Texture *_texture = 0;
    int _spriteWidth = 0;
    int _spriteHeight = 0;
    int _numCols = 0;
    int _numRows = 0;
    int _xPad = 0;
    int _yPad = 0;
    std::vector<std::vector<int>> _matrix;

};
#endif
