#ifndef UI_STATIC_TEXT_BOX_HPP
#define UI_STATIC_TEXT_BOX_HPP

#include "SDL.h"
#include "SDL_ttf.h"
#include "real_point.hpp"
#include "sprite.hpp"
#include "util.hpp"
#include <string>

class UiStaticTextBox : public Sprite {
  public:
    // i guess we want a an SDL_Rect for the background splash and two SDL_Color s
    // for the text and for the bg splash
    UiStaticTextBox(RealPoint, std::string, int, std::string, int, int, SDL_Renderer*);
    ~UiStaticTextBox();
    void render(SDL_Renderer*);

  protected:
    SDL_Texture *_fontTexture = 0;

};
#endif
