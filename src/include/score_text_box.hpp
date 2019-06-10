#ifndef SCORE_TEXT_BOX_HPP
#define SCORE_TEXT_BOX_HPP

#include "SDL.h"
#include "SDL_ttf.h"
#include "real_point.hpp"
#include "sprite.hpp"
#include "util.hpp"
#include <string>
#include "ui_dynamic_text_box.hpp"

class ScoreTextBox : public UiDynamicTextBox {
  public:
    ScoreTextBox(RealPoint, std::string, int, std::string, int, int, SDL_Renderer*);
    ~ScoreTextBox();
    void render(SDL_Renderer*);
    void setScore(int);
    int getScore();
    void incScore(int=1);

  protected:
    int _score = 0;

};
#endif
