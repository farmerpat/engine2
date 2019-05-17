#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
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
    Piece(RealPoint, std::string, SDL_Renderer*, std::vector<std::vector<int>>);
    ~Piece();
    void rotateClockwise();
    void rotateCounterClockwise();
    void render(SDL_Renderer*);
    void update(float);
    int getBitAt(int,int);
    void setBitAt(int,int,int);
    bool someBlockSet();

  protected:
    SDL_Texture *_blockTexture = 0;
    std::vector<std::vector<int>> _blockMap;
    char _blockWidth = 8;
    char _numCols = 3;
    char _numRows = 3;

};
#endif
