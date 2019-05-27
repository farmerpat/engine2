#ifndef INVADERZ_MATRIX_LEVEL_HPP
#define INVADERZ_MATRIX_LEVEL_HPP

#include <memory>
#include "SDL.h"
#include "../real_point.hpp"
#include "../screen_matrix.hpp"
#include "../game_manager.hpp"
#include "../level.hpp"
#include "../hero_sprite.hpp"
#include "../ui_text.hpp"
#include "../enemy_sprite_ellipsis.hpp"
#include "../invaderz_matrix.hpp"

class InvaderzMatrixLevel : public Level {
  public:
    InvaderzMatrixLevel(SDL_Renderer*);
    ~InvaderzMatrixLevel();
};
#endif
