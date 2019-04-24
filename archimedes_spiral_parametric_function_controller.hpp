#ifndef ARCHIMEDES_SPIRAL_PARAMETRIC_FUNCTION_CONTROLLER_HPP
#define ARCHIMEDES_SPIRAL_PARAMETRIC_FUNCTION_CONTROLLER_HPP

#include "parametric_function_controller.hpp"
#include <cmath>

class ArchimedesSpiralParametricFunctionController : public ParametricFunctionController {
  public:
    ArchimedesSpiralParametricFunctionController(Sprite*, double, float, float, float);
    void calculateY() override;
    void calculateX() override;

  protected:
    float _xOffset = 0;
    float _yOffset = 0;

};
#endif
