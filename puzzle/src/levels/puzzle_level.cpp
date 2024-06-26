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

    RealPoint mPos = { 64, 64 };
    this->_backgroundMatrix = std::shared_ptr<MatrixOfSprites>(
      new MatrixOfSprites(
        mPos, 16, 16, 46, 32, 0, 0, 1, 1, "assets/gray_bg_block.png", renderer

      )
    );

    gm->addIntToDictionary("screenMatrixMinX", mPos.X());
    gm->addIntToDictionary("screenMatrixMinY", mPos.Y());

    gm->addIntToDictionary("screenMatrixMaxX",
      mPos.X() + this->_backgroundMatrix->getWidth() * this->_backgroundMatrix->getNumCols()
    );

    gm->addIntToDictionary(
      "screenMatrixMaxY",
      mPos.Y() + this->_backgroundMatrix->getHeight() * this->_backgroundMatrix->getNumRows()
    );

    // TODO: i guess rm this. or at least stop doing it if its not going to be used
    //this->generatePieceList();
  } else {
    std::cout << "puzzle_level can't find file(s)\n";
  }

  RealPoint p1 = { 3.0, -3.0 };
  ScreenMatrix m1(3,3,0);
  m1.setBitAt(1,1,1);

  std::shared_ptr<PuzzleBackgroundHole> h1 = std::shared_ptr<PuzzleBackgroundHole>(
    new PuzzleBackgroundHole(p1, m1)
  );

  this->_bgHoles.push_back(
    std::move(
      h1
    )
  );

  RealPoint p2 = { 3.0, 5.0 };

  // this is tedious. make sub-classes
  ScreenMatrix m2(3,3,1);
  m2.setBitAt(0,0,0);
  m2.setBitAt(0,1,0);
  m2.setBitAt(0,2,0);
  m2.setBitAt(1,2,0);
  m2.setBitAt(2,2,0);

  RealPoint tp = { 3.0, 3.0 };
  std::shared_ptr<Sprite> uit = std::shared_ptr<Sprite>(
    new ScoreTextBox(
      tp, "assets/fonts/slkscr.ttf", 16, "Score: ", 75, 25
    )
  );

  this->addUiElement(uit);

  this->_levelController = new PuzzleLevelController(this);
}

void PuzzleLevel::setBgHoleBit(int pieceMatrixPositionX, int pieceMatrixPositionY, int pieceRow, int pieceCol, int val) {
  std::vector<std::shared_ptr<PuzzleBackgroundHole>>::size_type i, len;
  std::vector<std::shared_ptr<PuzzleBackgroundHole>> holes = this->_bgHoles;
  len = holes.size();

  int backgroundTargetX = pieceMatrixPositionX + pieceCol;
  int backgroundTargetY = pieceMatrixPositionY + pieceRow;

  for (i=0; i<len; i++) {
    std::shared_ptr<PuzzleBackgroundHole> &pbh = holes[i];
    RealPoint holePos = pbh->getMatrixPos();
    int holeX = (int)holePos.X();
    int holeY = (int)holePos.Y();

    for (int x=holeX; x<holeX+3; x++) {
      for (int y=holeY; y<holeY+3; y++) {

        if (x == backgroundTargetX && y == backgroundTargetY) {
          pbh->getHoleMap().setBitAt(x-holeX, y-holeY, val);
          goto leaveloop;
        }
      }
    }

leaveloop:
    ;

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

void PuzzleLevel::removeFilledHoles() {
  this->_bgHoles.erase(
    std::remove_if(
      this->_bgHoles.begin(),
      this->_bgHoles.end(),
      [](std::shared_ptr<PuzzleBackgroundHole> &pbh) {
        return !pbh->isAlive();
      }
    ),
    this->_bgHoles.end()
  );
}

void PuzzleLevel::setGameOver() {
  Level::setGameOver();

  // TODO:
  // add a UiDynamicTextBox _uiElements
}

void PuzzleLevel::incScore(int inc) {
  std::vector<std::unique_ptr<Sprite>>::size_type i, len;
  len = this->_uiElements.size();

  for (i=0; i<len; i++) {

    std::shared_ptr<Sprite> sprite = this->_uiElements[i];
    std::shared_ptr<ScoreTextBox> stb = std::static_pointer_cast<ScoreTextBox>(sprite);

    if (stb) {
      stb->incScore(inc);

    }
  }
}
