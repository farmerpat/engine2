#ifndef O_PIECE_HPP
#define O_PIECE_HPP

#include <vector>
#include <string>
#include "util.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "real_point.hpp"
#include "screen_matrix.hpp"
#include "piece.hpp"
#include "piece_controller.hpp"

class OPiece : public Piece {
  public:
    OPiece(RealPoint, SDL_Renderer*);
    void rotateClockwise();
    void rotateCounterClockwise();
    void distortLeft();
    void distortRight();
    void distortUp();
    void distortDown();
    //static const std::vector<std::vector<int>> _map;
    static ScreenMatrix _map;

  protected:
    //static const std::vector<std::vector<int>> _map = { {1,1,1}, {1,0,1}, {1,1,1}};
};
#endif
