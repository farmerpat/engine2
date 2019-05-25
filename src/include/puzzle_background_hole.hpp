#ifndef PUZZLE_BACKGROUND_HOLE_HPP
#define PUZZLE_BACKGROUND_HOLE_HPP

#include <vector>
#include <memory>
#include "real_point.hpp"
#include "puzzle_background_hole_controller.hpp"
#include "death_timer_puzzle_background_hole_controller.hpp"

class PuzzleBackgroundHoleController;

class PuzzleBackgroundHole {
  public:
    PuzzleBackgroundHole(RealPoint, std::vector<std::vector<int>>);
    virtual ~PuzzleBackgroundHole();
    void addController(std::unique_ptr<PuzzleBackgroundHoleController>);
    bool isAlive();
    void kill();
    void update();
    RealPoint getMatrixPos();
    std::vector<std::vector<int>> getHoleMap();
    void setBitAt(int, int, int);

  protected:
    bool _alive = true;
    RealPoint _parentMatrixPos;
    std::vector<std::unique_ptr<PuzzleBackgroundHoleController>> _controllers;
    std::vector<std::vector<int>> _holeMap;
};
#endif
