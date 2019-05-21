#ifndef PIECE_CONTROLLER_HPP
#define PIECE_CONTROLLER_HPP

#include "SDL.h"
#include "controller.hpp"
//#include "piece.hpp"
#include "levels/puzzle_level.hpp"
#include "game_manager.hpp"

class Piece;

class PieceController : public Controller {
  public:
    PieceController(Piece*);
    void update(float) override;

  private:
    Piece *_piece = 0;
    // i think that these should be coming from Piece
    // or from GameManager, or from somewhere...
    // e.g. should be "blockWidth" or something
    int _moveSize = 8;
    int _gravity = 8;
    int _gravityFrameCounter = 0;
    int _gravityFrameDelay = 30;
};

#endif
