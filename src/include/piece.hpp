#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include "util.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "real_point.hpp"
#include "sprite.hpp"
#include "piece_controller.hpp"

class Piece : public Sprite {
  public:
    Piece(RealPoint, std::string, SDL_Renderer*);
    ~Piece();
    void rotateClockwise();
    void rotateCounterClockwise();
    void render(SDL_Renderer*);
    void update(float);
    int getBitAt(int,int);
    void setBitAt(int,int,int);

  protected:
    SDL_Texture *_blockTexture = 0;
    int _blockMap[3][3] = { {1, 1, 1}, {1, 0, 1}, {1, 1, 1} };
    char _blockWidth = 8;
    char _numCols = 3;
    char _numRows = 3;

};
#endif
