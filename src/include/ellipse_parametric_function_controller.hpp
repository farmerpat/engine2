#ifndef ELLIPSE_PARAMETRIC_FUNCTION_CONTROLLER_HPP
#define ELLIPSE_PARAMETRIC_FUNCTION_CONTROLLER_HPP

#include "parametric_function_controller.hpp"
#include <cmath>

class EllipseParametricFunctionController : public ParametricFunctionController {
  public:
    EllipseParametricFunctionController(Sprite*, double, float, float, float, float, float);
    void calculateY() override;
    void calculateX() override;

  protected:
    float _xOffset = 0;
    float _yOffset = 0;
    float _radius = 1.0;
    float _a = 1.0;
    float _b = 1.0;

};

#endif
