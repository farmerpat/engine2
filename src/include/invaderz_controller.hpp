#ifndef INVADERZ_CONTROLLER_HPP
#define INVADERZ_CONTROLLER_HPP

#include "controller.hpp"
#include "matrix_of_sprites.hpp"
#include "real_point.hpp"

// this will have to ask the matrix sprite for the
// left- and right-most columns that have "alive" sprites
// and set the bounds based on that. it could also gradually
// move toward the player if we want.
class InvaderzController : public Controller {
  public:
    InvaderzController(MatrixOfSprites*, int, int, float);
    ~InvaderzController();
    virtual void update(float) override;

  protected:
    MatrixOfSprites *_sprite = 0;
    int _xMin = 0;
    int _xMax = 0;
    float _incX = 1.0;
    bool _movingRight = true;

};
#endif
