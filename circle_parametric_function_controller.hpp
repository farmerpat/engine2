#ifndef CIRCLE_PARAMETRIC_FUNCTION_CONTROLLER_HPP
#define CIRCLE_PARAMETRIC_FUNCTION_CONTROLLER_HPP

#include "parametric_function_controller.hpp"
#include <cmath>

class CircleParametricFunctionController : public ParametricFunctionController {
  public:
    CircleParametricFunctionController(Sprite*, double, float, float, float, float);
    void calculateY() override;
    void calculateX() override;

  protected:
    float _xOffset = 0;
    float _yOffset = 0;
    float _radius = 1.0;

};

#endif
