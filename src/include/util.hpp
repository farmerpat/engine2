#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Util {
  public:
    static SDL_Texture* loadTexture(std::string, SDL_Renderer*);
    static SDL_Texture* loadFontTexture(std::string, std::string, int, SDL_Color, SDL_Renderer*);

};
#endif
