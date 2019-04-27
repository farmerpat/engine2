#include "parametric_function_controller.hpp"
#include <cmath>

ParametricFunctionController::ParametricFunctionController
(Sprite* s, double tmax, float scale = 1.0) :
  FunctionController(s) {
  this->_tScale = scale;
  this->_tMax = tmax;
}

void ParametricFunctionController::update(float dt) {
  this->_t += (dt * this->_tScale);

  if (this->_t >= this->_tMax) {
    this->_t = this->_tMax;
    this->_tScale *= -1.0;

  } else if (this->_t < 0) {
    this->_t = 0.0;
    this->_tScale *= -1.0;

  }

  this->calculateX();
  this->calculateY();

  if (this->_loop) {
    if (!this->_firstTSeen) {
      this->_firstTSeen = true;
      this->_tFirstValue = this->_t;
      this->_xFirstValue= this->_currentX;
      this->_yFirstValue= this->_currentY;

    } else {
      // TODO(?): once we calculate this once, we can store it and not math so much
      // for additional loops
      if (std::abs(this->_currentX - this->_xFirstValue) < this->_loopTolerance) {
        if (std::abs(this->_currentY - this->_yFirstValue) < this->_loopTolerance) {
          //this->_t = 0.0;
          this->_t = dt;

        }
      }
    }
  }

  this->_sprite->setPos(this->_currentX, this->_currentY);
}

void ParametricFunctionController::setLoop() {
  this->_loop = true;
}

void ParametricFunctionController::clearLoop() {
  this->_loop = false;
}

void ParametricFunctionController::setLoopTolerance(float tol) {
  this->_loopTolerance = tol;
}
