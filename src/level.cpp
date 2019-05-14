#include "include/level.hpp"

Level::Level(SDL_Renderer*) {
  // when HeroController adds a sprite during update,
  // we get a segfault when _sprite's capacity == _sprite's size
  // strangely the segfault does not appear when _aiController
  // adds a sprite. this mitigates that issue

  // a more flexible approach might be
  // store the ptrs to be added in a separate
  // container and adding them before we
  // call removeDeadSprites
  this->_sprites.reserve(100);
}

Level::~Level() {
  this->_sprites.clear();

  if (_texture) {
    SDL_DestroyTexture(this->_texture);
  }
}

void Level::update(float dt) {
  std::vector<std::unique_ptr<Sprite>>::size_type i, len;
  len = this->_sprites.size();

  for (i=0; i<len; i++) {
    std::unique_ptr<Sprite> &sprite = this->_sprites[i];

    if (sprite->_controller) {
      Controller *c = sprite->_controller;

      if (c) {
        c->update(dt);
      }
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
  for (auto &s1 : this->_sprites) {

    if (!s1->isActive()) {
      continue;
    }

    for (auto &s2 : this->_sprites) {
      if (s1 == s2) {
        continue;
      }

      if (!s2->isActive()) {
        continue;
      }

      if (s1->getLayer() & s2->getLayer()) {
        // TODO:
        // can't expect a "normal" sprite to know how to deal with an aggregate,
        // so let the aggregate tell us
        // eventually, aggregates should be standardized in some way so that
        // we can handle the case where two aggregates collide. at that point,
        // an AggregateSprite class ought to be created. atm i just don't know
        // what that should look like.
        if (s2->isAggregate()) {
          if (s2->isCollidingWith(s1)) {
            s1->collisionHandler(s2);

          }
        } else if (s1->isCollidingWith(s2)) {
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
  this->_sprites.erase(
    std::remove_if(
      this->_sprites.begin(),
      this->_sprites.end(),
      [](auto const &sprite) { return !sprite || !sprite->isAlive(); }
    ),
    this->_sprites.end()
  );
}

void Level::renderBackgroundElements(SDL_Renderer *renderer) {
  // probably store background clear color in gamemanager
  // and use that to clear first
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  for (auto &sprite : this->_backgroundElements) {
    if (!sprite->isActive()) {
      continue;
    }
    sprite->render(renderer);
  }
}

void Level::renderSprites(SDL_Renderer *renderer) {
  for (auto &sprite : this->_sprites) {
    if (!sprite->isActive()) {
      continue;
    }
    sprite->render(renderer);

    if (GameManager::getInstance()->getDrawHitBoxes()) {
      if (sprite->getHitBox()) {
        SDL_Rect hb = sprite->getGlobalHitBox();

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
  }
}

void Level::renderUiElements(SDL_Renderer *renderer) {
  for (auto &sprite : this->_uiElements) {
    if (!sprite->isActive()) {
      continue;
    }

    sprite->render(renderer);
  }
}

void Level::render(SDL_Renderer* renderer) {
  this->renderBackgroundElements(renderer);
  this->renderSprites(renderer);
  this->renderUiElements(renderer);

  SDL_RenderPresent(renderer);
}

void Level::addBackgroundElement(std::unique_ptr<Sprite> sprite) {
  this->_backgroundElements.push_back(std::move(sprite));
}

void Level::addSprite(std::unique_ptr<Sprite> sprite) {
  this->_sprites.push_back(std::move(sprite));
}

void Level::addUiElement(std::unique_ptr<Sprite> sprite) {
  this->_uiElements.push_back(std::move(sprite));
}

std::unique_ptr<Sprite> &Level::getSpriteByTag(std::string tag) {
  for (auto &sprite : this->_sprites) {
    if (sprite->getTag() == tag) {
      return sprite;
    }
  }
}
