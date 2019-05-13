#ifndef UI_TEXT_HPP
#define UI_TEXT_HPP

#include "SDL.h"
#include "SDL_ttf.h"
#include "real_point.hpp"
#include "sprite.hpp"
#include "util.hpp"
#include <string>

class UiText : public Sprite {
  public:
    UiText(RealPoint, std::string, int, std::string, int, int, SDL_Renderer*);
    virtual ~UiText();
    void render(SDL_Renderer*);

  protected:
    SDL_Texture *_fontTexture = 0;

};
#endif
