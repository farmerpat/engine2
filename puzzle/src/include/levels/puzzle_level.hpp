#ifndef PUZZLE_LEVEL_HPP
#define PUZZLE_LEVEL_HPP

#include <string>
#include <memory>
#include "SDL.h"
#include "include/real_point.hpp"
#include "include/util.hpp"
#include "include/game_manager.hpp"
#include "include/level.hpp"
#include "include/sprite.hpp"
#include "include/piece.hpp"
#include "include/matrix_of_sprites.hpp"
#include "include/level_controller.hpp"
#include "include/puzzle_level_controller.hpp"
#include "include/puzzle_background_hole.hpp"
#include "include/ui_dynamic_text_box.hpp"
#include "include/score_text_box.hpp"

class PuzzleLevel : public Level {
  public:
    PuzzleLevel(SDL_Renderer*, std::string, std::string);
    ~PuzzleLevel();
    std::shared_ptr<MatrixOfSprites> getBackgroundMatrix();
    void render(SDL_Renderer*);
    std::vector<std::vector<int>> grabRandomPieceMap();
    std::vector<std::shared_ptr<PuzzleBackgroundHole>> getBgHoles();
    void setBgHoleBit(int, int, int, int, int);
    void removeFilledHoles();
    void setGameOver();
    void incScore(int=1);

  protected:
    std::shared_ptr<MatrixOfSprites> _backgroundMatrix;
    std::vector<std::vector<std::vector<int>>> _pieceList;
    std::vector<std::shared_ptr<PuzzleBackgroundHole>> _bgHoles;
    std::string _levelFileName;
    std::string _piecesFileName;
    void generatePieceList();

};

#endif
