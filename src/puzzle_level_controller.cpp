// TODO:
// add something to make the game more stressful.
// e.g.:
//  - platforms or projectiles that scroll up from
//  the bottom that destroy the pieces and punish
//  the player
//  - scroll the background infinitely, generating
//  holes
//
// also, since the piece list is going to be a thing,
// we could automatically generate bg holes on the fly
// from rotations of the pieces in the pool.

#include "include/piece.hpp"
#include "include/o_piece.hpp"
#include "include/puzzle_level_controller.hpp"
#include "include/levels/puzzle_level.hpp"
#include <iostream>

PuzzleLevelController::PuzzleLevelController(PuzzleLevel *level) : LevelController() {
  this->_puzzleLevel = level;
}

PuzzleLevelController::~PuzzleLevelController() {}

void PuzzleLevelController::update(float dt) {
  // TODO: make it an actual game!
  // e.g. keep track of the total holes that must be filled...
  // the time between deploying new holes regardless of whether others
  // have been filled. the number of holes that have disappeard before
  // being filled, etc.
  //
  // i want this to feel like an arcade game in the sense that:
  //  1. the player will die if they do nothing
  //  2. eventually, the player will die even with perfect play
  //
  // to start, add one piece that dies after a time.
  // start putting the spawned piece in the middle of the matrix.
  // after a piece dies or is filled, add another.
  //
  // at some point soon:
  // start keeping track of "level" and either(and?) decrease
  // time before hole death / increase number of holes
  //
  // could also stop using holes that are the same shape as peices,
  // and start making more random holes

  if (!this->_puzzleLevel->getBackgroundMatrix()->getMatrix().someEmptyBlocks() &&
      this->_puzzleLevel->getBgHoles().size() == 0
      ) {
    // open a win modal, and tell the gm to transition to the next
    // level somehow...
    std::cout << "you are super player!\n";
    // nope, add another hole

  } else {
    // TODO: its better to just clobber the bg matrix map with one entirely
    // consisting of ones...probably do that instead
    // set the entire matrix to 1s
    std::shared_ptr<MatrixOfSprites> bgMatrix = this->_puzzleLevel->getBackgroundMatrix();

    int rows = this->_puzzleLevel->getBackgroundMatrix()->getNumRows();
    int cols =  this->_puzzleLevel->getBackgroundMatrix()->getNumCols();

    for (int x=0; x<cols; x++) {
      for (int y=0; y<rows; y++) {
        this->_puzzleLevel->getBackgroundMatrix()->getMatrix().setBitAt(x, y, 1);

      }
    }

    // iterate over _bgHoles, call update on each of them, then clear the appropriate bits
    // in bg matrix
    std::vector<std::shared_ptr<PuzzleBackgroundHole>>::size_type i, len;
    std::vector<std::shared_ptr<PuzzleBackgroundHole>> holes = this->_puzzleLevel->getBgHoles();
    len = holes.size();

    for (i=0; i<len; i++) {
      std::shared_ptr<PuzzleBackgroundHole> &pbh = holes[i];
      pbh->update();

      if (pbh->isAlive()) {
        RealPoint mp = pbh->getMatrixPos();
        ScreenMatrix holeMap = pbh->getHoleMap();
        int startRow = (int)mp.X();
        int startCol = (int)mp.Y();
        int endRow = startRow+3;
        int endCol = startCol+3;

        for (int x=0, row=startRow; row<endRow; row++, x++) {
          for (int y=0, col=startCol; col<endCol; col++, y++) {
            this->_puzzleLevel->
              getBackgroundMatrix()->
              getMatrix().setBitAt(row, col, holeMap.getBitAt(x,y));
          }
        }
      }
      // remove the dead ones...
    }

    // if theres no active pieces on the screen, add a a new one.
    if (!this->pieceOnScreen()) {
      this->deployPiece();

    }
  }
}

bool PuzzleLevelController::pieceOnScreen() {
  bool pred = false;
  const std::vector<std::unique_ptr<Sprite>> &sprites = this->_puzzleLevel->getSprites();

  for (auto &sprite : sprites) {
    if (sprite->getTag() == "puzzle_piece") {
      pred = true;
      break;
    }
  }

  return pred;
}

void PuzzleLevelController::deployPiece() {
  GameManager *gm = GameManager::getInstance();

  if (gm) {
    int screenWidth = gm->getScreenWidth();
    int screenHeight = gm->getScreenHeight();

    SDL_Renderer *renderer = gm->getWindowRenderer();

    RealPoint pPos = { (screenWidth/2.0), 0.0 };
    // a factory instead of this.
    //std::vector<std::vector<int>> map = this->_puzzleLevel->grabRandomPieceMap();

    // TODO: rotate the piece randomly?

    // do i want to to just keep randomly sending peices? do i want intelligently
    // send them only pieces they can use or do i want to send garabge
    // sometimes (e.g. pick a piece shape from the list randomly)?
    // or do i just want to generate pieces completely randomly?
    //std::unique_ptr<Sprite> pinkPiece = std::unique_ptr<Sprite>(
      //new Piece(pPos, "assets/pink_block.png", renderer, map)
    //);

    // TODO: implement a PieceFactory class to get a specific piece (given an enum I guess)
    // or return a random one

    std::unique_ptr<Sprite> pinkPiece = std::unique_ptr<Sprite>(
      new OPiece(pPos, renderer)
    );

    this->_puzzleLevel->addSprite(std::move(pinkPiece));
  }
}
