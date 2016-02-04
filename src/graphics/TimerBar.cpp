#include "TimerBar.h"

const string TimerBar::TIMERBAR_FRAME_FILE_PATH = "timerbar_frame.png";
const string TimerBar::TIMERBAR_SHAFT_FILE_PATH = "timerbar_shaft.png";

TimerBar::TimerBar(unsigned timeout, int x, int y, int width, int height, SDL_Renderer* renderer) :
    Sprite(TIMERBAR_FRAME_FILE_PATH, x, y, width, height, renderer),
    timeout(timeout),
    counter(0),
    _ratio(0),
    timerBarShaft(NULL)
{
    this->timerBarShaft = new Sprite(TIMERBAR_SHAFT_FILE_PATH, x+FRAME_BORDER, y+FRAME_BORDER, 0, rect.h - FRAME_BORDER*2, renderer);
    this->shaftMaxWidth = rect.w - FRAME_BORDER*2;
}

TimerBar::~TimerBar()
{
    delete this->timerBarShaft;
}

void TimerBar::onDraw(SDL_Renderer* renderer) {
    this->timerBarShaft->onDraw(renderer);
    Sprite::onDraw(renderer);
}

void TimerBar::onUpdate(const unsigned elapsedTime) {
    counter += elapsedTime/1000.0;
    _ratio = counter / timeout;
    if(_ratio <= 1.01) {
        timerBarShaft->setWidth( _ratio * shaftMaxWidth );
    }
}
