#ifndef TIMERBAR_H
#define TIMERBAR_H

#include "Sprite.h"

class TimerBar : public Sprite
{
    unsigned timeout;
    float counter; // count elapsed time(ms) since init
    float _ratio;  // time VS shaft width
    Sprite* timerBarShaft;
    unsigned shaftMaxWidth;


    public:
        static const string TIMERBAR_FRAME_FILE_PATH;
        static const string TIMERBAR_SHAFT_FILE_PATH;
        static const short FRAME_BORDER = 3; // pixels

        // timeout - maximum time(in seconds) until reach the end
        TimerBar(unsigned timeout, int x, int y, int width, int height, SDL_Renderer* renderer);
        virtual ~TimerBar();
        void onDraw(SDL_Renderer* renderer);
        void onUpdate(const unsigned elapsedTime);
};

#endif // TIMERBAR_H
