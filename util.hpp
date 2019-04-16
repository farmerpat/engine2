#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include "SDL.h"
#include "SDL_image.h"

class Util {
  public:
    static SDL_Texture* loadTexture (std::string, SDL_Renderer*);

};
#endif
