// TODO:
// i wonder how crazy it is to update/render/etc from w/it an sdl timer callback.
// is there any benefit to doing this over sleeping as we do now?
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "include/real_point.hpp"
#include "include/config.hpp"
#include "include/game_manager.hpp"
#include "include/util.hpp"
#include "include/sprite.hpp"
#include "include/piece.hpp"
#include "include/hero_sprite.hpp"
#include "include/rectangular_primitive_sprite.hpp"
#include "include/level.hpp"
#include "include/path.hpp"
#include "include/path_controller.hpp"
#include "include/sine_function_of_x_controller.hpp"
#include "include/archimedes_spiral_parametric_function_controller.hpp"
#include "include/ellipse_parametric_function_controller.hpp"
#include "include/involute_of_a_circle_parametric_function_controller.hpp"
#include "include/enemy_sprite_ellipsis.hpp"
#include "include/enemy_sprite_sine.hpp"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>

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
  srand(time(0));
  Config config("../config.ini");
  SDL_Window *window = 0;
  SDL_Renderer *renderer = 0;
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

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    std::cout << "could not initialize sdl:" << std::endl;
    std::cout << SDL_GetError() << std::endl;
    std::cout << "bailing..." << std::endl;
    return 1;
  }

  int imgFlags = IMG_INIT_PNG;

  if (!(IMG_Init(imgFlags) & imgFlags)) {
    std::cout << "could not initialize sdl IMG" << std::endl;
    std::cout << IMG_GetError() << std::endl;
    std::cout << "bailing..." << std::endl;
    return 1;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cout << "could not initialize sdl Mixer" << std::endl;
    std::cout << Mix_GetError() << std::endl;
    std::cout << "bailing..." << std::endl;
    return 1;
  }

  gm = GameManager::getInstance();
  gm->setScreenWidth(SCREEN_WIDTH);
  gm->setScreenHeight(SCREEN_HEIGHT);

  if (config.query("draw_hitboxes") == "yes") {
    gm->setDrawHitBoxes();
  }

  window = SDL_CreateWindow("fyf",
      window_pos.x,
      window_pos.y,
      window_size.x,
      window_size.y,
      SDL_WINDOW_OPENGL);

  /*
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

      // TODO: figure out why this would be half of the hitbox
      //RealPoint cPos = { (SCREEN_WIDTH/2.0) - (ess2->getHitBox()->w*.5), 55.0 };
      RealPoint cPos = { (SCREEN_WIDTH/2.0) - 16, 55.0 };
      EnemySpriteEllipsis *ese1 = new EnemySpriteEllipsis(cPos, renderer, 250.0, 20.0);

      float amplitude = 25.0;
      float freq = 0.07;
      RealPoint fPos = { 30.0, 110.0 };

      Level *testLevel = new Level(renderer);
      float minx = 32.0;
      float maxx = 617.0;

      float step = 48.0;
      int imax=9;

      for (int j=0; j<4; ++j) {
        imax=9;
        fPos.setY(fPos.Y()+40);

        for (int i=0; i<9; ++i) {
          testLevel->addSprite(
            new EnemySpriteSine(
              fPos, renderer, amplitude, freq, minx+(i*step), maxx-(imax*step)
            )
          );

          imax--;
        }
      }

      //RealPoint pPos = { (SCREEN_WIDTH/2.0), (SCREEN_HEIGHT/2.0) };
      //Piece *pinkPiece = new Piece(pPos, "../assets/pink_block.png", renderer);

      testLevel->addSprite(heroSprite);
      testLevel->addSprite(ese1);

      gm->setCurrentLevel(testLevel);
      gm->setWindowRenderer(renderer);
      gm->setHero(heroSprite);

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
        // should i be calculating this instead?
        testLevel->update(1/60.0);
        testLevel->resolveCollisions();
        testLevel->removeDeadSprites();
        testLevel->render(renderer);
        // TODO: really have to remove disabled (add killed?) spites from list and delete them.

        current_time = SDL_GetTicks();
        //std::cout <<
          //"sleeping for : " <<
          //SCREEN_TICKS_PER_FRAME - (current_time-start_time) <<
          //std::endl;

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

  delete gm;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  Mix_Quit();
  IMG_Quit();
  SDL_Quit();

  return 0;
}
