#ifndef SHOOT_IF_HERO_IN_RANGE_AI_CONTROLLER_HPP
#define SHOOT_IF_HERO_IN_RANGE_AI_CONTROLLER_HPP

#include "SDL.h"
#include "controller.hpp"
#include "real_point.hpp"
#include "sprite.hpp"
#include "game_manager.hpp"
#include "enemy_bullet_sprite.hpp"

// TODO:
// it probalby makes sense to use object orientation in some
// way so that this timer functionality can be reused elsewhere.
class ShootIfHeroInRangeAIController : public Controller {
  public:
    ShootIfHeroInRangeAIController(Sprite*);
    void update(float) override;
    void setCanShoot();
    void clearCanShoot();
    void removeTimer();

  protected:
    static Uint32 timerCallBack(Uint32 inteveral, void *param);// {
    Sprite *_sprite = 0;
    int _frameShotDelay = 90;
    int _frameShotDelayCounter = 0;
    Uint32 _shotDelay = 0;
    bool _canShoot = true;
    SDL_TimerID _callbackTimerId;

};
#endif
