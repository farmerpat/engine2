#ifndef SHOOT_IF_HERO_IN_RANGE_AI_CONTROLLER_HPP
#define SHOOT_IF_HERO_IN_RANGE_AI_CONTROLLER_HPP

#include "SDL.h"
#include "controller.hpp"
#include "real_point.hpp"
#include "sprite.hpp"
#include "game_manager.hpp"
#include "enemy_bullet_sprite.hpp"

class ShootIfHeroInRangeAIController : public Controller {
  public:
    ShootIfHeroInRangeAIController(Sprite*);
    void update(float) override;

  protected:
    Sprite *_sprite = 0;
    int _frameShotDelay = 90;
    int _frameShotDelayCounter = 0;

};
#endif
