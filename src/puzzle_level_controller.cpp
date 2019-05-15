#include "include/puzzle_level_controller.hpp"

PuzzleLevelController::PuzzleLevelController(Level *level) : LevelController(level) {}

PuzzleLevelController::~PuzzleLevelController() {}

void PuzzleLevelController::update(float dt) {
  // if theres no active pieces on the screen, add a a new one.
  if (!this->pieceOnScreen()) {
    this->deployPiece();
  }
}

bool PuzzleLevelController::pieceOnScreen() {
  bool pred = false;
  const std::vector<std::unique_ptr<Sprite>> &sprites = this->_level->getSprites();

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
    std::unique_ptr<Sprite> pinkPiece = std::unique_ptr<Sprite>(
      new Piece(pPos, "assets/pink_block.png", renderer)
    );

    this->_level->addSprite(std::move(pinkPiece));
  }
}
