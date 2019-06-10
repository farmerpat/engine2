#include "include/score_text_box.hpp"
#include <iostream>

ScoreTextBox::ScoreTextBox
(RealPoint pos, std::string font, int pt, std::string text, int w, int h)
  : UiDynamicTextBox (pos, font, pt, text, w, h) {

}


ScoreTextBox::~ScoreTextBox() {
  std::cout << "i r UiTextBox desctructor\n";
}

void ScoreTextBox::render(SDL_Renderer *ren) {

}

void ScoreTextBox::setScore(int);
int ScoreTextBox::getScore();
void ScoreTextBox::incScore(int inc) {

}


