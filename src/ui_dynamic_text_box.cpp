#include "include/ui_dynamic_text_box.hpp"
#include <iostream>

UiDynamicTextBox::UiDynamicTextBox
(RealPoint pos, std::string font, int pt, std::string text, int w, int h)
  : Sprite(pos, w, h) {

    this->_font = font;
    this->_point = pt;
    this->_text = text;
    this->_fontColor.r = 255;
    this->_fontColor.g = 255;
    this->_fontColor.b = 255;
    this->_fontColor.a = 255;

    this->_boxColor.r = 0;
    this->_boxColor.g = 0;
    this->_boxColor.b = 0;
    this->_boxColor.a = 255;
}

UiDynamicTextBox::~UiDynamicTextBox() { }

void UiDynamicTextBox::render(SDL_Renderer *renderer) {
  SDL_Rect texture_dest_rect;

  texture_dest_rect.x = (int)this->getPos()->X();
  texture_dest_rect.y = (int)this->getPos()->Y();
  texture_dest_rect.w = this->getWidth() * this->_xScale;
  texture_dest_rect.h = this->getHeight() * this->_yScale;

  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;

  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

  SDL_SetRenderDrawColor(
    renderer,
    this->_boxColor.r,
    this->_boxColor.g,
    this->_boxColor.b,
    this->_boxColor.a
  );

  SDL_RenderFillRect(renderer, &texture_dest_rect);
  SDL_SetRenderDrawColor(renderer, r, g, b, a);

  SDL_Texture *fontTexture = Util::loadFontTexture
    (this->_font, this->_text, this->_point, this->_fontColor, renderer);

  if (fontTexture) {
    SDL_RenderCopy(renderer, fontTexture, NULL, &texture_dest_rect);

    SDL_DestroyTexture(fontTexture);
  }
}

void UiDynamicTextBox::setFont(std::string f) {
  this->_font = f;
}

void UiDynamicTextBox::setPoint(int pt) {
  this->_point = pt;
}

void UiDynamicTextBox::setText(std::string text) {
  this->_text = text;
}
