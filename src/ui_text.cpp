#include "include/ui_text.hpp"

UiText::UiText
(RealPoint pos, std::string font, int pt, std::string text, int w, int h, SDL_Renderer *ren)
  : Sprite (pos, w, h) {
  SDL_Color color = {255, 255, 255};

  this->_fontTexture = Util::loadFontTexture(font, text, pt, color, ren);
}

// TODO: add a new constructor that takes a color

UiText::~UiText() {
  if (this->_fontTexture) {
    SDL_DestroyTexture(this->_fontTexture);
  }
}

void UiText::render(SDL_Renderer *renderer) {
  SDL_Rect texture_dest_rect;

  texture_dest_rect.x = (int)this->getPos()->X();
  texture_dest_rect.y = (int)this->getPos()->Y();
  texture_dest_rect.w = this->getWidth() * this->_xScale;
  texture_dest_rect.h = this->getHeight() * this->_yScale;

  SDL_RenderCopy(renderer, this->_fontTexture, NULL, &texture_dest_rect);
}
