#include "level.hpp"

Level::Level(SDL_Renderer*) {
  // make _texture the whole size of the renderer
}

Level::~Level() {
  // iterate over the sprites and free them
  // free _texture

  for (std::vector<Sprite>::size_type i = 0; i < this->_sprites.size(); i++) {
    delete this->_sprites[i];
  }
  // TODO:
  // do we want to erase and shrink this like in path?

  if (_texture) {
    SDL_DestroyTexture(this->_texture);
  }
}

void Level::update(float dt) {
  for (std::vector<Sprite>::size_type i = 0; i < this->_sprites.size(); i++) {
    Sprite *sprite = this->_sprites[i];

    if (sprite->_controller) {
      // maybe its bombing b/c it doesn't know
      // what kind of controller it is?
      // but then what is the point of polymorphism?
      // or maybe its because this is an arg to hero constructor
      // and this wasn't cast to sprite?

      // do i really have to dynamically cast this?
      // then what's the point?
      // maybe try creating HeroController and HeroSprite
      // separately and then adding it?
      // don't see how that would make a difference
      //
      // maybe its because HeroController has a memeber (sprite)
      // that Controller does not.
      //
      // it appears that it wasn't from passing "this" as arg.
      // i removed that and it bombed anyway
      //HeroController *c = std::dynamic_cast<HeroController*>(sprite->controller);
      Controller *c = sprite->_controller;

      if (c) {
        c->update(dt);
      }
      //sprite->controller->update(dt);
    }
  }
}

void Level::render(SDL_Renderer* renderer) {
  // probably store background clear color in gamemanager
  // and use that to clear first

  // keep a background color somewhere and use that.
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  for (std::vector<Sprite>::size_type i = 0; i < this->_sprites.size(); i++) {
    // TODO:
    // it seems like it would be faster to get a reference
    // to _sprites[i] than to keep referencing the vector all over the place.
    // investigate.

    this->_sprites[i]->render(renderer);


    // we may actually want to be copying to level's own texture and
    // render copying that after this loop


  }

  SDL_RenderPresent(renderer);
}

void Level::addSprite(Sprite* sprite) {
  this->_sprites.push_back(sprite);
}
