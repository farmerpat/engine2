#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include <string>
#include "util.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "real_point.hpp"
#include "screen_matrix.hpp"
#include "sprite.hpp"
#include "piece_controller.hpp"

class Piece : public Sprite {
  public:
    Piece(RealPoint, std::string, SDL_Renderer*);
    Piece(RealPoint, std::string, SDL_Renderer*, ScreenMatrix);
    virtual ~Piece();
    void render(SDL_Renderer*);
    void update(float);
    //ScreenMatrix const getMatrix() const;
    ScreenMatrix getMatrix();
    //int getBitAt(int,int);
    //void setBitAt(int,int,int);
    bool someBlockSet();
    // should this be delegated to ScreenMatrix?
    virtual void rotateClockwise() {};
    virtual void rotateCounterClockwise() {};
    // TODO: if i don't end up adding the ability to expand, rename these
    // should these be delegated to ScreenMatrix somehow?
    virtual void distortLeft()  {};
    virtual void distortRight() {};
    virtual void distortUp() {};
    virtual void distortDown() {};
    int getBlockWidth () { return this->_blockWidth; }

  protected:
    SDL_Texture *_blockTexture = 0;
    //std::vector<std::vector<int>> _blockMap;
    ScreenMatrix _blockMap;
    int _blockWidth = 8;
    char _numCols = 3;
    char _numRows = 3;

};
#endif
