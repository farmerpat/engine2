#include "../include/levels/puzzle_level.hpp"

PuzzleLevel::PuzzleLevel(SDL_Renderer *renderer) : Level(renderer) {
  GameManager *gm = GameManager::getInstance();

  if (gm) {
    int screenWidth = gm->getScreenWidth();
    int screenHeight = gm->getScreenHeight();

    RealPoint pPos = { (screenWidth/2.0), (screenHeight/2.0) };
    std::unique_ptr<Sprite> pinkPiece = std::unique_ptr<Sprite>(
      new Piece(pPos, "assets/pink_block.png", renderer)
    );

    this->addSprite(std::move(pinkPiece));
  }
}

PuzzleLevel::~PuzzleLevel() {
}
