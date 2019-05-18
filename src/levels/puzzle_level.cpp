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
        mPos, 8, 8, 64, 32, 0, 0, 1, 1, "../assets/gray_bg_block.png", renderer, map

      )
    );

    this->generatePieceList();
  } else {
    std::cout << "puzzle_level can't find file(s)";
  }

  /*
  if (gm) {
    int screenWidth = gm->getScreenWidth();
    int screenHeight = gm->getScreenHeight();

    RealPoint pPos = { (screenWidth/2.0), 0.0 };
    std::unique_ptr<Sprite> pinkPiece = std::unique_ptr<Sprite>(
      new Piece(pPos, "assets/pink_block.png", renderer)
    );

    this->addSprite(std::move(pinkPiece));

  }
  */

  this->_levelController = new PuzzleLevelController(this);
}

PuzzleLevel::~PuzzleLevel() {
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
