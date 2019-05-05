#include "include/util.hpp"

SDL_Texture* Util::loadTexture (std::string file, SDL_Renderer *renderer) {
  SDL_Texture *texture = NULL;
  SDL_Surface *surface = NULL;

  surface = IMG_Load(file.c_str());

  if (surface) {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
  }

  return texture;
}

