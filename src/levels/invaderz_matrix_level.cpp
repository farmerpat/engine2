#include "../include/levels/invaderz_matrix_level.hpp"

InvaderzMatrixLevel::InvaderzMatrixLevel(SDL_Renderer *renderer) : Level(renderer) {
  GameManager *gm = GameManager::getInstance();

  if (gm) {
    int screenWidth = gm->getScreenWidth();
    int screenHeight = gm->getScreenHeight();

    RealPoint heroPos = { screenWidth/2.0, screenHeight*(13/16.0) };
    std::unique_ptr<Sprite> heroSprite = std::unique_ptr<Sprite>(
      new HeroSprite(heroPos, renderer)
    );

    this->addSprite(std::move(heroSprite));

    // TODO: figure out why this would be half of the hitbox
    //RealPoint cPos = { (SCREEN_WIDTH/2.0) - (ess2->getHitBox()->w*.5), 55.0 };
    RealPoint cPos = { (screenWidth/2.0) - 16, 55.0 };
    std::unique_ptr<Sprite> ese = std::unique_ptr<Sprite>(
      new EnemySpriteEllipsis(cPos, renderer, 250.0, 20.0)
    );

    this->addSprite(std::move(ese));

    /*
    int map[3][10] = {
      //{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
      //{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 1 },
      { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
      { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
      { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };

    int *mapRows[3] = { map[0], map[1], map[2] };
    int **ptrMap = mapRows;
    */

    //std::unique_ptr<Sprite> mat = std::unique_ptr<Sprite>(
    //new MatrixOfSprites(
    //mPos, 16, 16, 2, 10, 30, 30, 2, 2, "assets/enemy1_single_frame.png", renderer, mapRows
    //)
    //);

    ScreenMatrix mapRows(10, 3, 1);

    RealPoint mPos = { 30.0, 110.0 };
    std::unique_ptr<Sprite> mat = std::unique_ptr<Sprite>(
      new InvaderzMatrix(
        mPos, 16, 16, 3, 10, 30, 30, 2, 2, renderer, mapRows
      )
    );

    this->addSprite(std::move(mat));

    RealPoint fontPos { 0.0, 0.0 };
    std::unique_ptr<Sprite> fyfText = std::unique_ptr<Sprite>(
      new UiText(fontPos, "assets/fonts/slkscr.ttf", 16, "fyfalot", 75, 25, renderer)
    );

    this->addUiElement(std::move(fyfText));
  }
}

InvaderzMatrixLevel::~InvaderzMatrixLevel() {}
