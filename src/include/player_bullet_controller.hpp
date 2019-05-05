#ifndef PLAYER_BULLET_CONTROLLER_HPP
#define PLAYER_BULLET_CONTROLLER_HPP

#include "controller.hpp"
#include "sprite.hpp"

// TODO: does it make sense to just alter Controller
// to have a constructor that takes a sprite and
// has an update that just moves?
// i bet it does.
class PlayerBulletController : public Controller {
  public:
    PlayerBulletController(Sprite*);
    void update(float) override;

  protected:
    Sprite *_sprite = 0;
};
#endif
