#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

//#include "sprite.hpp"

class Controller {
  public:
    //Controller (Sprite *s) { _sprite = s; }
    //Controller(Sprite*);
    virtual void update(float dt) { }
    virtual ~Controller(void);

  //protected:
    //Sprite *_sprite = 0;
};
#endif
