#ifndef FUNCTION_CONTROLLER_HPP
#define FUNCTION_CONTROLLER_HPP

#include "controller.hpp"
#include "sprite.hpp"

class FunctionController : public Controller {
  public:
    FunctionController(Sprite*);
    //~FunctionController();
    virtual void update(float) override;
    // if continuous functions aren't
    // used, things may get weird
    virtual void calculateY();
    virtual void calculateX();
    void setYDependsOnX();
    void clearYDependsOnX();
    void setInitialX(float);
    void setInitialY(float);
    void setMinX(float);
    void setMinY(float);
    void setMaxX(float);
    void setMaxY(float);
    void setXInc(float);
    void setYInc(float);
    void setOscillating();
    void clearOscillating();

  protected:
    Sprite *_sprite = 0;
    bool _yDependsOnX = true;
    bool _oscillating = false;

    float _initialX = 0.0;
    float _minX = 0.0;
    float _maxX = 0.0;
    float _xInc = 1.0;
    float _currentX = 0.0;

    float _initialY = 0.0;
    float _minY = 0.0;
    float _maxY = 0.0;
    float _yInc = 1.0;
    float _currentY = 0.0;

};
#endif
