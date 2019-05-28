#ifndef PUZZLE_BACKGROUND_HOLE_HPP
#define PUZZLE_BACKGROUND_HOLE_HPP

#include <vector>
#include <memory>
#include "real_point.hpp"
#include "screen_matrix.hpp"
#include "puzzle_background_hole_controller.hpp"
#include "death_timer_puzzle_background_hole_controller.hpp"
#include "oscillate_right_left_puzzle_background_hole_controller.hpp"

// TODO:
// if want fade out effect on kill, use texture instead of emptiness
class PuzzleBackgroundHoleController;

class PuzzleBackgroundHole {
  public:
    PuzzleBackgroundHole(RealPoint, ScreenMatrix);
    virtual ~PuzzleBackgroundHole();
    void addController(std::unique_ptr<PuzzleBackgroundHoleController>);
    bool isAlive();
    void kill();
    void update();
    RealPoint getMatrixPos();
    void setMatrixPos(RealPoint);
    ScreenMatrix &getHoleMap();

  protected:
    bool _alive = true;
    RealPoint _parentMatrixPos;
    std::vector<std::unique_ptr<PuzzleBackgroundHoleController>> _controllers;
    ScreenMatrix _holeMap;
};
#endif
