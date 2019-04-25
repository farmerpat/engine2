#ifndef INVOLUTE_OF_A_CIRCLE_PARAMETRIC_FUNCTION_CONTROLLER_HPP
#define INVOLUTE_OF_A_CIRCLE_PARAMETRIC_FUNCTION_CONTROLLER_HPP

#include "parametric_function_controller.hpp"
#include <cmath>

class InvoluteOfACircleParametricFunctionController : public ParametricFunctionController {
  public:
    InvoluteOfACircleParametricFunctionController(Sprite*, double, float, float, float, float);
    void calculateY() override;
    void calculateX() override;

  protected:
    float _xOffset = 0;
    float _yOffset = 0;
    float _radius = 1.0;

};

#endif
