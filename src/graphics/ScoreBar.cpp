#include "ScoreBar.h"

const string ScoreBar::TIMERBAR_FRAME_FILE_PATH = "scorebar_frame.png";
const string ScoreBar::TIMERBAR_SHAFT_FILE_PATH = "scorebar_shaft.png";

ScoreBar::ScoreBar(float maxScore, int x, int y, int width, int height, SDL_Renderer* renderer) :
    Sprite(TIMERBAR_FRAME_FILE_PATH, x, y, width, height, renderer),
    score(0),
    maxScore(maxScore),
    _ratio(0),
    timerBarShaft(NULL)
{
    this->timerBarShaft = new Sprite(TIMERBAR_SHAFT_FILE_PATH, x+FRAME_BORDER, y+FRAME_BORDER, 0, rect.h - FRAME_BORDER*2, renderer);
    this->shaftMaxWidth = rect.w - FRAME_BORDER*2;
}

ScoreBar::~ScoreBar()
{
    delete this->timerBarShaft;
}

void ScoreBar::onDraw(SDL_Renderer* renderer) {
    this->timerBarShaft->onDraw(renderer);
    Sprite::onDraw(renderer);
}

void ScoreBar::incrementScore(int score) {
    this->score += score;
    _ratio = this->score / maxScore;
    if(_ratio > 1.0) {
        _ratio = 1;
    }
    timerBarShaft->setWidth( _ratio * shaftMaxWidth );
}

void ScoreBar::reset() {
    this->_ratio = 0.0;
    this->score = 0;
}
