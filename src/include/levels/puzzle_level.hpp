#ifndef PUZZLE_LEVEL_HPP
#define PUZZLE_LEVEL_HPP

#include <string>
#include <memory>
#include "SDL.h"
#include "../real_point.hpp"
#include "../util.hpp"
#include "../game_manager.hpp"
#include "../level.hpp"
#include "../sprite.hpp"
#include "../piece.hpp"
#include "../matrix_of_sprites.hpp"
#include "../level_controller.hpp"
#include "../puzzle_level_controller.hpp"
#include "../puzzle_background_hole.hpp"

class PuzzleLevel : public Level {
  public:
    PuzzleLevel(SDL_Renderer*, std::string, std::string);
    ~PuzzleLevel();
    std::shared_ptr<MatrixOfSprites> getBackgroundMatrix();
    void render(SDL_Renderer*);
    std::vector<std::vector<int>> grabRandomPieceMap();
    std::vector<std::shared_ptr<PuzzleBackgroundHole>> getBgHoles();
    void setBgHoleBit(int, int, int, int, int);

  protected:
    std::shared_ptr<MatrixOfSprites> _backgroundMatrix;
    std::vector<std::vector<std::vector<int>>> _pieceList;
    std::vector<std::shared_ptr<PuzzleBackgroundHole>> _bgHoles;
    std::string _levelFileName;
    std::string _piecesFileName;
    void generatePieceList();

};

#endif
