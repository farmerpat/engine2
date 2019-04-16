#include "textured_sprite.hpp"

TexturedSprite::TexturedSprite(SDL_Point pos, int w, int h, std::string img, SDL_Renderer *r)
  : Sprite (pos, w, h) {
  //this->_pos = pos;
  //this->_width = w;
  //this->_height = h;
  this->_texture = Util::loadTexture(img, r);
}

TexturedSprite::~TexturedSprite() {
  if (this->_texture) {
    SDL_DestroyTexture(this->_texture);

  }
}

SDL_Texture *TexturedSprite::getTexture(void) {
  return this->_texture;
}

void TexturedSprite::render(SDL_Renderer *renderer) {
  // maybe make this a member and just update it
  SDL_Rect texture_dest_rect;

  texture_dest_rect.x = this->getPos()->x;
  texture_dest_rect.y = this->getPos()->y;
  texture_dest_rect.w = this->getWidth();
  texture_dest_rect.h = this->getHeight();

  // renderer, texture, source_rect, dest_rect
  SDL_RenderCopy(renderer, this->_texture, NULL, &texture_dest_rect);
}
