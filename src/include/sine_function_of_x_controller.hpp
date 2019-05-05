#ifndef SINE_FUNCTION_OF_X_CONTROLLER
#define SINE_FUNCTION_OF_X_CONTROLLER

#include "function_controller.hpp"
#include <cmath>

class SineFunctionOfXController : public FunctionController {
  public:
    SineFunctionOfXController(Sprite*, float, float);
    // we can leave calculate x the same
    void calculateY() override;

  protected:
    float _amplitude = 1.0;
    float _frequency = 1.0;

};
#endif
