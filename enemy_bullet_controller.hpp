#ifndef ENEMY_BULLET_CONTROLLER_HPP
#define ENEMY_BULLET_CONTROLLER_HPP

#include "controller.hpp"
#include "sprite.hpp"

class EnemyBulletController : public Controller {
  public:
    EnemyBulletController(Sprite*);
    void update(float) override;

  protected:
    Sprite *_sprite = 0;
};
#endif
