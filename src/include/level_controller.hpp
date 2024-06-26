#ifndef level_controller_hpp
#define level_controller_hpp

#include "controller.hpp"
#include "level.hpp"

class Level;

class LevelController : public Controller {
  public:
    LevelController();
    LevelController(Level*);
    ~LevelController();
    virtual void update(float dt) { }

  protected:
    Level *_level;
};
#endif
