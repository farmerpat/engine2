#include "SDL.h"
#include "SDL_image.h"
#include "real_point.hpp"
#include "game_manager.hpp"
#include "util.hpp"
#include "sprite.hpp"
#include "hero_sprite.hpp"
#include "rectangular_primitive_sprite.hpp"
#include "level.hpp"
#include "path.hpp"
#include "path_controller.hpp"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

// TODO: use valgrind to check profiling, look for leaks, etc
// TODO: use a namespace, you barbarian
// TODO: consider a Game object, but don't force it
// TODO: use a timer and hold to 60 fps
// TODO: consider C before this gets too crazy...
//        ...it might be really cool to create a lisp ffi for this

// TODO: clean up these globals
static bool up_pressed_this_frame = false;
static bool down_pressed_this_frame = false;
static bool left_pressed_this_frame = false;
static bool right_pressed_this_frame = false;
static bool a_pressed_this_frame = false;
static bool b_pressed_this_frame = false;
static bool x_pressed_this_frame = false;
static bool y_pressed_this_frame = false;
static bool lb_pressed_this_frame = false;
static bool rb_pressed_this_frame = false;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

static bool quit = false;
static GameManager *gm;

void clearFrameInputFlags (void) {
  up_pressed_this_frame = false;
  down_pressed_this_frame = false;
  left_pressed_this_frame = false;
  right_pressed_this_frame = false;
  a_pressed_this_frame = false;
  b_pressed_this_frame = false;
  x_pressed_this_frame = false;
  y_pressed_this_frame = false;
  lb_pressed_this_frame = false;
  rb_pressed_this_frame = false;

}

// probably move this and parsePlayerInput
// to GameManager or a util class or something
void cleanUpInput(GameManager *gm) {
  if (!up_pressed_this_frame) {
    gm->playerInput.upPressed = false;
    gm->playerInput.upJustPressed = false;
  }

  if (!down_pressed_this_frame) {
    gm->playerInput.downPressed = false;
    gm->playerInput.downJustPressed = false;
  }

  if (!left_pressed_this_frame) {
    gm->playerInput.leftPressed = false;
    gm->playerInput.leftJustPressed = false;
  }

  if (!right_pressed_this_frame) {
    gm->playerInput.rightPressed = false;
    gm->playerInput.rightJustPressed = false;
  }

  if (!a_pressed_this_frame) {
    gm->playerInput.aPressed = false;
    gm->playerInput.aJustPressed = false;
  }
}

void parsePlayerInput (GameManager *gm, SDL_Event e) {
  // TODO: add gamepad support
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
      case SDLK_UP:
        up_pressed_this_frame = true;

        if (gm->playerInput.upPressed) {
          gm->playerInput.upJustPressed = false;

        } else {
          gm->playerInput.upPressed = true;
          gm->playerInput.upJustPressed = true;
        }
        break;

      case SDLK_DOWN:
        down_pressed_this_frame = true;

        if (gm->playerInput.downPressed) {
          gm->playerInput.downJustPressed = false;

        } else {
          gm->playerInput.downPressed = true;
          gm->playerInput.downJustPressed = true;
        }
        break;

      case SDLK_LEFT:
        left_pressed_this_frame = true;

        if (gm->playerInput.leftPressed) {
          gm->playerInput.leftJustPressed = false;

        } else {
          gm->playerInput.leftPressed = true;
          gm->playerInput.leftJustPressed = true;
        }
        break;

      case SDLK_RIGHT:
        right_pressed_this_frame = true;

        if (gm->playerInput.rightPressed) {
          gm->playerInput.rightJustPressed = false;

        } else {
          gm->playerInput.rightPressed = true;
          gm->playerInput.rightJustPressed = true;
        }
        break;

      case SDLK_SPACE:
        a_pressed_this_frame = true;

        if (gm->playerInput.aPressed) {
          gm->playerInput.aJustPressed = false;

        } else {
          gm->playerInput.aPressed = true;
          gm->playerInput.aJustPressed = true;
        }
        break;

    }
  }
}

int main (int argc, char **argv) {
  gm = GameManager::getInstance();
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *texture = NULL;
  SDL_Event e;

  SDL_Point window_pos = {
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED
  };

  SDL_Point window_size = {
    640,
    480
  };

  SDL_Rect texture_dest_rect;
  texture_dest_rect.x = 0;
  texture_dest_rect.y = 0;
  texture_dest_rect.w = 32;
  texture_dest_rect.h = 32;

  SDL_Init(SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow("fyf",
      window_pos.x,
      window_pos.y,
      window_size.x,
      window_size.y,
      SDL_WINDOW_OPENGL);

  /*
   * i want a sprite to be able to have a width/height,
   * be positionable (have a controller? either input or AI),
   * be animateable,
   * and to be composed of a texture or a primitive shape,
   * and to have a hitbox and have an optional collision callback
   * could be either "static" or "dynamic", where static is like a
   * tile? or a cannon or a spike that doesn't move.
   * having a level have an optional tileset makes more sense
   * that creating sprites for every single tile
   * will need Tiled parser. can draw tilemap hitboxes in Tiled
   * and convert to SDL_Rect(s)
   *
   * overall, i want the code to somehow be flexible
   */

  /*
   * shower thoughts:
   *  make a GameManager struct (single global instance) or class (singleton)
   *  that doesn't depend on any other classes in the engine besides input.
   *  for instance, it doesn't know what a Level is, but has an int currentLevelIndex
   *  that can be called upon by another global LevelCollection to get access
   *  to the current level (previously some Actors depended on Scene's existence)
   *  ...this particular example might not solve that problem...
   *  also, it can hold hero position w/o knowing what a HeroSprite (or whatever)
   *  is. this may not be OOP best practices, but so what? classes depending on
   *  eachother is fucked in my opinion
   *
   *  GM will also have playerInput array, number of players, etc
   *  PlayerInput can be struct that gets written to in game loop
   *  only boolens udlr, abxy, lt rt. hopefully pressed/justpressed. thassit
   *  can just use playerInput alone to start.
   *
   *  eff the Game class, just have main for now.
   *  main will have game loop. it will read input, and
   *  update GameManager appropriately. It can then look
   *  at its current level and ask it to render all its shit, handle collisions,
   *  etc.
   *
   *  every sprite can have a pointer to an SDL_Rect hitbox to start.
   *  in theory could (should?) also implement an array of hitboxes
   *  (perhaps usually of length 1) that get checked for collisions.
   *
   *  maybe to start, i only care about hero collisions and other actors
   *  colliding with static things/ eachother is a logic error...
   *
   *  sprite descendents all have render method that must be overriden
   *  PrimitiveSprite, TexturedSprite
   *  sprites should also have controllers that either read player input
   *  or are driven by paths somehow. the most primitive sprites won't
   *  move at all. others will have paths. others paths will change depending
   *  on Hero's position.
   *
   *  could also specify animation paths as functions of time (e.g. i assume galaga)
   *  TODO:
   *    learn how to rotate a sine wave
   *    https://youtu.be/BPgq2AudoEo?t=834
   *
   *
   *    movement contollers....
   *    surely there must be some pattern that will allow me to
   *    plug in a controller to a sprite...
   *    player controlled controller
   *    two point oscillator controller...
   *    n point oscillator controller
   *    fn controller...
   *    decorator pattern? dependency injection? i have no idea.
   *    if using decorator pattern, the controller could be changed
   *    at run time.
   *
   *
   *    decorator might work. a la https://www.youtube.com/watch?v=j40kRwSm4VE,
   *    could have abstract Controller
   *    implement concrete StaticController (getNextPos(currentPos) returns currentPos)
   *    e.g. Absract LinearDecorator Concrete PositiveLinearDecorator ?
   *    wait...i think we actually have an abstract sprite, concrete TexturedSprite
   *    that has an abstract ControllerDecorator
   *    w/ this pattern, Sprite would an interface in another language...in c++
   *    the equivalent of an interface is an abstract class w/ only pure virtual fns
   *
   *    i think decorator is wrong. seems like it gets used to add multiples
   *    like if we wanted a thing to have multiple controllers?
   *
   *    what i really want is a controller class (or descendants of it) that is
   *    flexible enough to react to user input, but also be controlled by a path
   *
   *    a Controller class being a member of sprites might be good enough...
   *    Level::update can call controller on each sprite if its controller is not null
   *    i made playerInput globally accessible via GM so particular controllers can
   *    just peek the input. a PathController could have a path field and can get information
   *    about its Sprite via dependancy injection (e.g. _controller = new PathController(this)
   *    i think that will work
   *
   *
   *    TODO:
   *      probably "cleaner" to use a singleton for GM
   */
  if (window) {
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer) {
      RealPoint heroPos = { 10.0, 10.0 };
      HeroSprite *heroSprite = new HeroSprite(heroPos, renderer);
      RealPoint rPos = { 0.0, 100.0 };
      //TexturedSprite *testSprite = new TexturedSprite(p, 32, 32, "./slug_right.png", renderer);
      RectangularPrimitiveSprite *rSprite = new RectangularPrimitiveSprite(rPos, 300, 15);
      Path *path = new Path();
      RealPoint controllerPoint;
      controllerPoint.setX(rPos.X());
      controllerPoint.setY(rPos.Y());
      path->addNode(controllerPoint);
      controllerPoint.setX(rPos.X() + 300);
      controllerPoint.setY(rPos.Y());
      path->addNode(controllerPoint);

      PathController *pc = new PathController(rSprite, path);
      rSprite->controller = pc;

      Level *testLevel = new Level(renderer);
      testLevel->addSprite(heroSprite);

      //SDL_Point heroPos2 = { 100, 100 };
      //HeroSprite *heroSprite2 = new HeroSprite(heroPos2, renderer);
      //testLevel->addSprite(heroSprite2);

      testLevel->addSprite(rSprite);

      //texture = Util::loadTexture("./slug_right.png", renderer);

      unsigned int last_time = 0, current_time;
      float dt;

      while (!quit) {
        clearFrameInputFlags();

        while(SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) {
            quit = true;

          } else {
            parsePlayerInput(gm, e);
          }
        }

        // now i think we can send levels per-frame input w/ justPressed "buttons"
        // the level will iterate over its sprites and render them.
        cleanUpInput(gm);
        //SDL_RenderClear(renderer);
        // renderer, texture, source_rect, dest_rect
        //SDL_RenderCopy(renderer, texture, NULL, &texture_dest_rect);
        //SDL_RenderPresent(renderer);
        current_time = SDL_GetTicks();
        // if we are using a wait, shouldn't we always
        // be sending the same dt?
        // derp....
        // or the wait should be before update and render or something
        // could try monkeying around with the order,
        // or could just try moving to
        // std::this_thread::sleep_for(std::chrono::milliseconds(x))
        // ^ requires c++ 11
        dt = (current_time - last_time) / 1000.0f;
        testLevel->update(dt);
        //testLevel->update(1/60.0);
        testLevel->render(renderer);

        //last_time = current_time;
        // this value keeps oscillating by an order of magnitude...
        // wtf
        std::cout << current_time-last_time << std::endl;
        if ((current_time-last_time) < SCREEN_TICKS_PER_FRAME) {
          //SDL_Delay(SCREEN_TICKS_PER_FRAME - (current_time-last_time));
          std::this_thread::sleep_for(
            std::chrono::milliseconds(
              SCREEN_TICKS_PER_FRAME - (current_time-last_time)
            )
          );
        }

        last_time = current_time;

        // weekend's goal:
        // create a level that draws controllable hero sprite
        // and a primitive rectangle sprite that is controlled
        // by a path

      }
    }
  }

  //SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
