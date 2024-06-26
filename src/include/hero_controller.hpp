#ifndef HERO_CONTROLLER
#define HERO_CONTROLLER

#include "SDL.h"
#include "controller.hpp"
#include "sprite.hpp"
#include "game_manager.hpp"
//TODO: rename to hero_
#include "player_bullet_sprite.hpp"

class HeroController : public Controller {
  public:
    HeroController();
    HeroController(Sprite*);
    void update(float) override;

  private:
    Sprite *_sprite = 0;
};

#endif
