#include "include/puzzle_background_hole.hpp"

PuzzleBackgroundHole::PuzzleBackgroundHole(RealPoint pos, std::vector<std::vector<int>> map) {
  this->_parentMatrixPos = pos;
  this->_holeMap = map;

  std::unique_ptr<PuzzleBackgroundHoleController> deathController =
    std::unique_ptr<PuzzleBackgroundHoleController>(
        new DeathTimerPuzzleBackgroundHoleController(this, 480)
    );

  this->_controllers.push_back(std::move(deathController));
}

PuzzleBackgroundHole::~PuzzleBackgroundHole() {
  this->_controllers.clear();
}

void PuzzleBackgroundHole::addController(std::unique_ptr<PuzzleBackgroundHoleController> ctrl) {
  this->_controllers.push_back(std::move(ctrl));
}

bool PuzzleBackgroundHole::isAlive() {
  return this->_alive;
}

void PuzzleBackgroundHole::kill() {
  this->_alive = false;
}

void PuzzleBackgroundHole::update() {
  std::vector<std::unique_ptr<PuzzleBackgroundHoleController>>::size_type i, len;
  len = this->_controllers.size();

  for (i=0; i<len; i++) {
    std::unique_ptr<PuzzleBackgroundHoleController> &ctrl = this->_controllers[i];

    // TODO: otherwise, remove it!
    if (ctrl->isActive()) {
      ctrl->update();
    }
  }
}

RealPoint PuzzleBackgroundHole::getMatrixPos() {
  return this->_parentMatrixPos;
}

std::vector<std::vector<int>> PuzzleBackgroundHole::getHoleMap() {
  return this->_holeMap;
}

void PuzzleBackgroundHole::setBitAt(int row, int col, int val) {
  this->_holeMap[row][col] = val;
}
