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
#include "sine_function_of_x_controller.hpp"
#include "archimedes_spiral_parametric_function_controller.hpp"
#include "ellipse_parametric_function_controller.hpp"
#include "involute_of_a_circle_parametric_function_controller.hpp"
#include "enemy_sprite.hpp"
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
static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

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

static bool up_input_stale = false;
static bool down_input_stale = false;
static bool left_input_stale = false;
static bool right_input_stale = false;
static bool a_input_stale = false;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

static bool quit = false;
static GameManager *gm;

void clearFrameInputFlags () {
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

void dropStaleInputs () {
  if (up_input_stale) {
    gm->playerInput.upPressed = false;
    gm->playerInput.upJustPressed = false;
    up_input_stale = false;
  }

  if (down_input_stale) {
    gm->playerInput.downPressed = false;
    gm->playerInput.downJustPressed = false;
    down_input_stale = false;
  }

  if (left_input_stale) {
    gm->playerInput.leftPressed = false;
    gm->playerInput.leftJustPressed = false;
    left_input_stale = false;
  }

  if (right_input_stale) {
    gm->playerInput.rightPressed = false;
    gm->playerInput.rightJustPressed = false;
    right_input_stale = false;
  }

  if (a_input_stale) {
    gm->playerInput.aPressed = false;
    gm->playerInput.aJustPressed = false;
    a_input_stale = false;
  }
}

// probably move this and parsePlayerInput
// to GameManager or a util class or something
void cleanUpInput(GameManager *gm) {
  if (!up_pressed_this_frame) {
    gm->playerInput.upJustPressed = false;
  }

  if (!down_pressed_this_frame) {
    gm->playerInput.downJustPressed = false;
  }

  if (!left_pressed_this_frame) {
    gm->playerInput.leftJustPressed = false;
  }

  if (!right_pressed_this_frame) {
    gm->playerInput.rightJustPressed = false;
  }

  if (!a_pressed_this_frame) {
    gm->playerInput.aJustPressed = false;
  }
}

void parsePlayerInput (GameManager *gm, SDL_Event e) {
  // TODO: add gamepad support
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
      case SDLK_UP:
        if (!e.key.repeat) {
          up_pressed_this_frame = true;
          gm->playerInput.upPressed = true;
          gm->playerInput.upJustPressed = true;
        }

        break;

      case SDLK_DOWN:
        if (!e.key.repeat) {
          down_pressed_this_frame = true;
          gm->playerInput.downPressed = true;
          gm->playerInput.downJustPressed = true;

        }
        break;

      case SDLK_LEFT:
        if (!e.key.repeat) {
          left_pressed_this_frame = true;
          gm->playerInput.leftPressed = true;
          gm->playerInput.leftJustPressed = true;

        }
        break;

      case SDLK_RIGHT:
        if (!e.key.repeat) {
          right_pressed_this_frame = true;
          gm->playerInput.rightPressed = true;
          gm->playerInput.rightJustPressed = true;

        }
        break;

      case SDLK_SPACE:
        if (!e.key.repeat) {
          a_pressed_this_frame = true;
          gm->playerInput.aPressed = true;
          gm->playerInput.aJustPressed = true;

        }
        break;

    }
  } else if (e.type == SDL_KEYUP) {
    switch (e.key.keysym.sym) {
      case SDLK_UP:
        if (!up_pressed_this_frame) {
          gm->playerInput.upPressed = false;
          gm->playerInput.upJustPressed = false;

        } else {
          up_input_stale = true;
        }
        break;

      case SDLK_DOWN:
        if (!down_pressed_this_frame) {
          gm->playerInput.downPressed = false;
          gm->playerInput.downJustPressed = false;
        } else {
          down_input_stale = true;
        }
        break;

      case SDLK_LEFT:
        if (!left_pressed_this_frame) {
          gm->playerInput.leftPressed = false;
          gm->playerInput.leftJustPressed = false;
        } else {
          left_input_stale = true;
        }
        break;

      case SDLK_RIGHT:
        if (!right_pressed_this_frame) {
          gm->playerInput.rightPressed = false;
          gm->playerInput.rightJustPressed = false;
        } else {
          right_input_stale = true;
        }
        break;

      case SDLK_SPACE:
        if (!a_pressed_this_frame) {
          gm->playerInput.aPressed = false;
          gm->playerInput.aJustPressed = false;
        } else {
          a_input_stale = true;
        }
        break;

    }
  }
}

#undef main

int main (int argc, char **argv) {
  gm = GameManager::getInstance();
  gm->setScreenWidth(SCREEN_WIDTH);
  gm->setScreenHeight(SCREEN_HEIGHT);
  gm->setDrawHitBoxes();

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
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
   */
  if (window) {
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer) {
      RealPoint heroPos = { SCREEN_WIDTH/2.0, SCREEN_HEIGHT*(13/16.0) };
      // TODO: move this to HeroSprite constructor
      SDL_Rect hb;
      hb.x = 0;
      hb.y = 0;
      hb.w = 64;
      hb.h = 64;

      HeroSprite *heroSprite = new HeroSprite(heroPos, renderer);
      heroSprite->setHitBox(hb);
      heroSprite->setLayer(1);

      RealPoint fPos = { 30.0, 300.0 };
      RectangularPrimitiveSprite *fSprite =
        new RectangularPrimitiveSprite(fPos, 15, 15);

      hb.w = 15;
      hb.h = 15;
      fSprite->setHitBox(hb);
      fSprite->setLayer(1);
      fSprite->setTag("enemy_ship");

      // TODO:
      // makes more sense to pass RealPoint to FunctionController
      // constructor.
      SineFunctionOfXController *sfc =
        new SineFunctionOfXController(fSprite, 25.0, 0.05);

      sfc->setMinX(30.0);
      sfc->setMaxX(600.0);
      // "speed"
      sfc->setXInc(2.5);
      sfc->setOscillating();

      fSprite->_controller = sfc;

      RealPoint f2Pos = { 30.0, 280.0 };
      RectangularPrimitiveSprite *f2Sprite =
        new RectangularPrimitiveSprite(f2Pos, 15, 15);

      hb.w = 15;
      hb.h = 15;
      f2Sprite->setHitBox(hb);
      f2Sprite->setLayer(1);
      f2Sprite->setTag("enemy_ship");

      SineFunctionOfXController *sfc2 =
        new SineFunctionOfXController(f2Sprite, 25.0, 0.05);

      sfc2->setMinX(30.0);
      sfc2->setMaxX(600.0);
      sfc2->setXInc(2.5);
      sfc2->setOscillating();

      f2Sprite->_controller = sfc2;

      hb.w = 32;
      hb.h = 32;
      RealPoint cPos = { (SCREEN_WIDTH/2.0)-hb.w, 75.0 };

      EnemySprite *eSprite = new EnemySprite(cPos, hb, renderer);

      Level *testLevel = new Level(renderer);
      testLevel->addSprite(heroSprite);
      testLevel->addSprite(fSprite);
      testLevel->addSprite(f2Sprite);
      testLevel->addSprite(eSprite);

      gm->setCurrentLevel(testLevel);
      gm->setWindowRenderer(renderer);

      unsigned int last_time = 0, current_time;
      unsigned int start_time = 0;
      float dt;

      while (!quit) {
        start_time = SDL_GetTicks();

        // if keyup and keydown for the same key
        // come in on the same frame, wait to clear
        // them until the next frame
        // TODO: test that this actually
        // works by seeding inputs via SDL_PushEvent.
        dropStaleInputs();

        clearFrameInputFlags();

        while(SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) {
            quit = true;

          } else {
            parsePlayerInput(gm, e);
          }
        }

        cleanUpInput(gm);
        //dt = (current_time - last_time) / 1000.0f;
        testLevel->update(1/60.0);
        testLevel->resolveCollisions();
        testLevel->render(renderer);
        // TODO: really have to remove disabled (add killed?) spites from list and delete them.

        current_time = SDL_GetTicks();
        if ((current_time-start_time) < SCREEN_TICKS_PER_FRAME) {
          std::this_thread::sleep_for(
            std::chrono::milliseconds(
              SCREEN_TICKS_PER_FRAME - (current_time-start_time)

            )
          );
        }
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
