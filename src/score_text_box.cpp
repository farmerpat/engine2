#include "include/score_text_box.hpp"

ScoreTextBox::ScoreTextBox
(RealPoint pos, std::string font, int pt, std::string scoreText, int w, int h)
  : UiDynamicTextBox (pos, font, pt, scoreText, w, h) {
    this->_scoreText = scoreText;
}

ScoreTextBox::~ScoreTextBox() { }

void ScoreTextBox::render(SDL_Renderer *ren) {
  std::string text = this->_scoreText + std::to_string(this->_score);
  this->_text = text;
  UiDynamicTextBox::render(ren);
}

void ScoreTextBox::setScore(int s) {
  this->_score = s;
}

int ScoreTextBox::getScore() {
  return this->_score;
}

void ScoreTextBox::incScore(int inc) {
  this->_score += inc;
}
