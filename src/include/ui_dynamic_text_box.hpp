#ifndef UI_DYNAMIC_TEXT_BOX_HPP
#define UI_DYNAMIC_TEXT_BOX_HPP

#include "SDL.h"
#include "SDL_ttf.h"
#include "real_point.hpp"
#include "sprite.hpp"
#include "util.hpp"
#include <string>

class UiDynamicTextBox : public Sprite {
  public:
    UiDynamicTextBox(RealPoint, std::string, int, std::string, int, int);
    // since Sprite's destructor
    // is virtual, all the parents destructors will get called...
    // (e.g. this doesn't have to be virtual)
    ~UiDynamicTextBox();
    void render(SDL_Renderer*);
    void setFont(std::string);
    void setPoint(int);
    void setText(std::string);

  protected:
    //SDL_Texture *_fontTexture = 0;
    std::string _font;
    int _point;
    std::string _text;
    SDL_Color _fontColor;
    SDL_Color _boxColor;

};
#endif
