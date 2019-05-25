#include "../include/levels/puzzle_level.hpp"
#include <iostream>

// TODO: there's only ~56 bg rows on screen. clean up the level txt file
PuzzleLevel::PuzzleLevel(SDL_Renderer *renderer, std::string levelFileName, std::string piecesFileName)
  : Level(renderer) {

  GameManager *gm = GameManager::getInstance();
  this->_levelFileName = levelFileName;
  this->_piecesFileName = piecesFileName;

  if (Util::fileExists(this->_levelFileName) && Util::fileExists(this->_piecesFileName)) {
    std::vector<std::vector<int>> map = Util::csvToVectorOfVectorsOfInts(this->_levelFileName);

    RealPoint mPos = { 192, 32 };
    this->_backgroundMatrix = std::shared_ptr<MatrixOfSprites>(
      new MatrixOfSprites(
        mPos, 8, 8, 64, 32, 0, 0, 1, 1, "assets/gray_bg_block.png", renderer, map

      )
    );

    // TODO: i guess rm this. or at least stop doing it if its not going to be used
    //this->generatePieceList();
  } else {
    std::cout << "puzzle_level can't find file(s)\n";
  }

  RealPoint p1 = { 20.0, 20.0 };
  std::vector<std::vector<int>> m1 = { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 }};

  std::shared_ptr<PuzzleBackgroundHole> h1 = std::shared_ptr<PuzzleBackgroundHole>(
    new PuzzleBackgroundHole(p1, m1)
  );

  this->_bgHoles.push_back(
    std::move(
      h1
    )
  );

  RealPoint p2 = { 3.0, 5.0 };
  std::vector<std::vector<int>> m2 = {
    { 0, 1, 1 },
    { 0, 1, 1 },
    { 0, 0, 0 }
  };

  std::shared_ptr<PuzzleBackgroundHole> h2 = std::shared_ptr<PuzzleBackgroundHole>(
    new PuzzleBackgroundHole(p2, m2)
  );

  this->_bgHoles.push_back(
    std::move(
      h2
    )
  );

  this->_levelController = new PuzzleLevelController(this);
}

void PuzzleLevel::setBgHoleBit(int matrixPositionX, int matrixPositionY, int pieceRow, int pieceCol, int val) {
  std::vector<std::shared_ptr<PuzzleBackgroundHole>>::size_type i, len;
  std::vector<std::shared_ptr<PuzzleBackgroundHole>> holes = this->_bgHoles;
  len = holes.size();

  for (i=0; i<len; i++) {
    std::shared_ptr<PuzzleBackgroundHole> &pbh = holes[i];
    RealPoint holePos = pbh->getMatrixPos();
    int x = (int)holePos.X();
    int y = (int)holePos.Y();

    if (x == matrixPositionX && y == matrixPositionY) {
      pbh->setBitAt(pieceRow, pieceCol, val);
      break;

    }
  }
}

PuzzleLevel::~PuzzleLevel() {
  this->_bgHoles.clear();
}

std::shared_ptr<MatrixOfSprites> PuzzleLevel::getBackgroundMatrix() {
  return this->_backgroundMatrix;
}

void PuzzleLevel::render(SDL_Renderer *renderer) {
  Level::renderBackgroundElements(renderer);

  if (this->_backgroundMatrix) {
    this->_backgroundMatrix->render(renderer);
  }

  Level::renderSprites(renderer);
  Level::renderUiElements(renderer);

  SDL_RenderPresent(renderer);
}

void PuzzleLevel::generatePieceList() {
  int i=0;
  std::vector<std::vector<int>> allPieces = Util::csvToVectorOfVectorsOfInts(this->_piecesFileName);
  std::vector<std::vector<int>> piece;

  for (auto &line : allPieces) {
    if (i == 3) {
      i=0;
      this->_pieceList.push_back(piece);
      piece.clear();
    }

    piece.push_back(line);
    i++;
  }

  if (i == 3) {
    this->_pieceList.push_back(piece);
  }
}

std::vector<std::vector<int>> PuzzleLevel::grabRandomPieceMap() {
  int index = Util::getRandomIntInRange(this->_pieceList.size());
  return this->_pieceList[index];
}

std::vector<std::shared_ptr<PuzzleBackgroundHole>> PuzzleLevel::getBgHoles() {
  return this->_bgHoles;
}
