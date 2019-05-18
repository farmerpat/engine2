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

#include "include/puzzle_level_controller.hpp"
#include <iostream>

PuzzleLevelController::PuzzleLevelController(PuzzleLevel *level) : LevelController() {
  this->_puzzleLevel = level;
}

PuzzleLevelController::~PuzzleLevelController() {}

void PuzzleLevelController::update(float dt) {
  if (!this->_puzzleLevel->getBackgroundMatrix()->someEmptyBlocks()) {
    // open a win modal, and tell the gm to transition to the next
    // level somehow...
    std::cout << "you are super player!\n";

  } else {
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
    //std::vector<std::vector<int>> map = { {1,1,1}, {1,0,1}, {1,1,1}};
    std::vector<std::vector<int>> map = this->_puzzleLevel->grabRandomPieceMap();
    // TODO: rotate the piece randomly?

    // do i want to to just keep randomly sending peices? do i want intelligently
    // send them only pieces they can use or do i want to send garabge
    // sometimes (e.g. pick a piece shape from the list randomly)?
    // or do i just want to generate pieces completely randomly?
    std::unique_ptr<Sprite> pinkPiece = std::unique_ptr<Sprite>(
      new Piece(pPos, "assets/pink_block.png", renderer, map)
    );

    this->_puzzleLevel->addSprite(std::move(pinkPiece));
  }
}
