#ifndef PUZZLE_BACKGROUND_HOLE_CONTROLLER_HPP
#define PUZZLE_BACKGROUND_HOLE_CONTROLLER_HPP

class PuzzleBackgroundHole;

class PuzzleBackgroundHoleController {
  public:
    PuzzleBackgroundHoleController(PuzzleBackgroundHole*);
    virtual void update();
    bool isActive();

  protected:
    PuzzleBackgroundHole *_hole = 0;
    bool _active = true;
};
#endif
