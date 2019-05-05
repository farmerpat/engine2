#include "include/level.hpp"

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

    if (sprite->_aiController) {
      Controller *aic = sprite->_aiController;

      if (aic) {
        aic->update(dt);
      }
    }
  }
}

void Level::resolveCollisions() {
  for (std::vector<Sprite>::size_type i = 0; i < this->_sprites.size(); i++) {
    Sprite *s1 = this->_sprites[i];

    if (!s1->isActive()) {
      continue;
    }

    for (std::vector<Sprite>::size_type j = 0; j < this->_sprites.size(); j++) {
      if (j == i) {
        continue;
      }

      Sprite *s2 = this->_sprites[j];

      if (!s2->isActive()) {
        continue;
      }

      if (s1->getLayer() & s2->getLayer()) {
        SDL_Rect hb1 = s1->getGlobalHitBox();
        SDL_Rect hb2 = s2->getGlobalHitBox();
        if (SDL_HasIntersection(&hb1, &hb2)) {
          // how to find which side collided...
          // if i use SDL_IntersectRect instead, it will
          // return the intersection rect.
          // by inspecting the intersection rect, i could probably
          // determine where i have to move s1 to resolve the collision
          // e.g. if s1 bottom overlaps s2 top, can adjust by intersect rect height
          // a la https://gamedev.stackexchange.com/questions/53476/resolving-2d-collision-with-rectangles
          // should also take velocity into account when resolving collisions for best
          // results i think. this may involve changing other controllers to use _velocity too
          // https://gamedev.stackexchange.com/questions/5428/how-can-i-implement-rectangle-collision-response/5433#5433
          // all of the above is about resolving collisions, for the shooter, i
          // only need the hero and enemies to be told that they have been hit.
          // this is enough for mvp
          s1->collisionHandler(s2);

        }
      }
    }
  }
}

void Level::removeDeadSprites() {

  for (std::vector<Sprite*>::iterator it = this->_sprites.begin(); it != this->_sprites.end();) {
    if (!(*it)->isAlive()) {
      delete *it;
      it = this->_sprites.erase(it);

    } else {
      it++;

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

    if (!this->_sprites[i]->isActive()) {
      continue;
    }

    // TODO remove killed sprites

    this->_sprites[i]->render(renderer);

    if (GameManager::getInstance()->getDrawHitBoxes()) {
      if (this->_sprites[i]->getHitBox()) {
        SDL_Rect hb = this->_sprites[i]->getGlobalHitBox();

        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
        SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
        SDL_SetRenderDrawColor(renderer, 17, 249, 44, 255);
        SDL_RenderDrawRect(renderer, &hb);
        SDL_SetRenderDrawColor(renderer, r, g, b, a);

      }
    }

    // we may actually want to be copying to level's own texture and
    // render copying that after this loop
  }

  SDL_RenderPresent(renderer);
}

void Level::addSprite(Sprite* sprite) {
  this->_sprites.push_back(sprite);
}
