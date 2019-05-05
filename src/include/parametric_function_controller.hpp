#ifndef PARAMETRIC_FUNCTION_CONTROLLER
#define PARAMETRIC_FUNCTION_CONTROLLER

#include "function_controller.hpp"

class ParametricFunctionController : public FunctionController {
  public:
    ParametricFunctionController(Sprite*, double, float);
    void update(float) override;
    virtual void calculateY() = 0;
    virtual void calculateX() = 0;
    void setLoop();
    void clearLoop();
    void setLoopTolerance(float);

  protected:
    double _t = 0.0;
    double _tMax = 0.0;
    float _tScale = 1.0;
    double _tLoopvalue = -1.0;
    double _tFirstValue = -1.0;
    float _xFirstValue = -1.0;
    float _yFirstValue = -1.0;
    float _loopTolerance = 0.01;
    bool _firstTSeen = false;
    bool _loop = false;
};
#endif
