#ifndef INVADERZ_AI_CONTROLLER_HPP
#define INVADERZ_AI_CONTROLLER_HPP

#include <memory>
#include <vector>
#include "SDL.h"
#include "controller.hpp"
#include "real_point.hpp"
#include "config.hpp"
#include "invaderz_matrix.hpp"
#include "game_manager.hpp"
#include "enemy_bullet_sprite.hpp"

class InvaderzMatrix;

class InvaderzAiController : public Controller {
  public:
    InvaderzAiController(InvaderzMatrix*);
    void update(float) override;

  protected:
    // TODO: this code is basically duplicated
    // but applied to matricies. think about
    // what refactoring could be done.
    bool rngAllowShot();
    InvaderzMatrix *_sprite = 0;
    int _frameShotDelay = 90;
    std::vector<std::vector<int>> _frameShotDelayCounterMatrix;
    std::vector<std::vector<bool>> _canShootMatrix;
    void initMatrices();
    float _shotChance = 0.0;
    void updateFrameShotDelay();

};

#endif
