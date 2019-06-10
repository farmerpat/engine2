#include "include/ui_text_box.hpp"
#include <iostream>

UiTextBox::UiTextBox
(RealPoint pos, std::string font, int pt, std::string text, int w, int h, SDL_Renderer *ren)
  : Sprite (pos, w, h) {
  SDL_Color color = {255, 255, 255};

  this->_fontTexture = Util::loadFontTexture(font, text, pt, color, ren);
  std::cout << "fyf\n";
}

UiTextBox::~UiTextBox() {
  if (this->_fontTexture) {
    SDL_DestroyTexture(this->_fontTexture);
  }
}

void UiTextBox::render(SDL_Renderer *renderer) {
  SDL_Rect texture_dest_rect;

  texture_dest_rect.x = (int)this->getPos()->X();
  texture_dest_rect.y = (int)this->getPos()->Y();
  texture_dest_rect.w = this->getWidth() * this->_xScale;
  texture_dest_rect.h = this->getHeight() * this->_yScale;

  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;

  // TODO: push/pop render draw color should be utility fns
  // push draw color
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  // just default to white bg for now.
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  // NOTE: may want a different rectangle for this
  SDL_RenderFillRect(renderer, &texture_dest_rect);
  // pop draw color draw color
  SDL_SetRenderDrawColor(renderer, r, g, b, a);

  SDL_RenderCopy(renderer, this->_fontTexture, NULL, &texture_dest_rect);
}
