#ifndef PATH_CONTROLLER_HPP
#define PATH_CONTROLLER_HPP

#include "controller.hpp"
#include "sprite.hpp"
#include "path.hpp"

class PathController : public Controller {
  public:
    PathController(Sprite*, Path*);
    ~PathController();
    void update(float) override;

  protected:
    Path *_path = 0;
    Sprite *_sprite = 0;
    // we will have to keep track of the origin,
    // the last node and the node we are headed to.
    // will have to figure out how to move toward
    // the next node from where the sprite is right now.
    // i think that means will have to pass in Sprite*
    // to constructor as well, so we have a reference to its
    // position. this feels like a (possibly circular) linked list.
    // the current node knows its own position, and how much time
    // is supposed to elapse on the way to the next position.
    // should also think about tolerances, e.g. if our next move
    // will put us 0.000001 pixels away from the next node, just put us there
    //
    // imagine if we could specify the transition function somehow.
    // like f(x) = x for straight shot
    // f(x) = x^2, etc...
    // arcs, whatever
    // parabollic curves?
    long double _timeSinceLastNode = 0.0;

};
#endif
