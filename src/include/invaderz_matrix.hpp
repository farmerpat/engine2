#ifndef INVADERZ_MATRIX_HPP
#define INVADERZ_MATRIX_HPP

#include "matrix_of_sprites.hpp"
#include "real_point.hpp"
#include "screen_matrix.hpp"
#include "invaderz_controller.hpp"
#include "invaderz_ai_controller.hpp"
#include <string>

class InvaderzMatrix : public MatrixOfSprites {
  public:
    InvaderzMatrix(RealPoint, int, int, int, int, int, int, int, int, SDL_Renderer*, ScreenMatrix);
    ~InvaderzMatrix();
};
#endif
