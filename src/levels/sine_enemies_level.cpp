#include "../include/levels/sine_enemies_level.hpp"

SineEnemiesLevel::SineEnemiesLevel(SDL_Renderer *renderer) : Level(renderer) {
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
    std::unique_ptr<Sprite> ese1 = std::unique_ptr<Sprite>(
      new EnemySpriteEllipsis(cPos, renderer, 250.0, 20.0)
    );

    this->addSprite(std::move(ese1));

    float amplitude = 25.0;
    float freq = 0.07;
    RealPoint fPos = { 30.0, 110.0 };

    float minx = 32.0;
    float maxx = 617.0;

    float step = 48.0;
    int imax=9;

    for (int j=0; j<4; ++j) {
      imax=9;
      fPos.setY(fPos.Y()+40);

      for (int i=0; i<9; ++i) {
        std::unique_ptr<Sprite> sprite = std::unique_ptr<Sprite>(
            new EnemySpriteSine(
              fPos, renderer, amplitude, freq, minx+(i*step), maxx-(imax*step)
              )
            );
        this->addSprite(std::move(sprite));
        imax--;

      }
    }
  }
}

SineEnemiesLevel::~SineEnemiesLevel() {
}
