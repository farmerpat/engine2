#include "include/util.hpp"

SDL_Texture *Util::loadTexture (std::string file, SDL_Renderer *renderer) {
  SDL_Texture *texture = 0;
  SDL_Surface *surface = 0;

  surface = IMG_Load(file.c_str());

  if (surface) {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
  }

  return texture;
}

// TODO:
// allow for setting style via TTF_SetFontStyle later
SDL_Texture *Util::loadFontTexture
(std::string file, std::string text, int pt, SDL_Color color, SDL_Renderer *rend) {
  SDL_Texture *texture = 0;
  SDL_Surface *surface = 0;

  TTF_Font *font = TTF_OpenFont(file.c_str(), pt);

  if (font) {
    surface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (surface) {
      texture = SDL_CreateTextureFromSurface(rend, surface);
      SDL_FreeSurface(surface);
    }


    TTF_CloseFont(font);
  }

  return texture;
}
