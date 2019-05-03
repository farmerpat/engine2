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
    static Uint32 timerCallBack(Uint32 inteveral, void *param);// {
      //_canShoot = true;
    //}
    Sprite *_sprite = 0;
    int _frameShotDelay = 90;
    int _frameShotDelayCounter = 0;
    Uint32 _shotDelay = 0;
    // i think this approach is the wrong solution... i believe this staitc
    // member will be shared among all instances. that is worthless w/ controller count > 1
    static bool _canShoot;

};
#endif
