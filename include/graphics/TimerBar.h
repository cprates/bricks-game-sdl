#ifndef TIMERBAR_H
#define TIMERBAR_H

#include "Sprite.h"

class GameScene;

class TimerBar : public Sprite
{
    /*
    template<typename T>
    struct TouchCallBack {
        typedef void (T::* type)();
    };*/

    unsigned timeout;
    float counter; // count elapsed time(ms) since init
    float _ratio;  // time VS shaft width
    Sprite* timerBarShaft;
    unsigned shaftMaxWidth;
    bool paused;
    typedef void (GameScene::* TimeoutCallback)();
    TimeoutCallback timeoutCallback;
    GameScene* parent;


    public:
        static const string TIMERBAR_FRAME_FILE_PATH;
        static const string TIMERBAR_SHAFT_FILE_PATH;
        static const short FRAME_BORDER = 3; // pixels

        // timeout - maximum time(in seconds) until reach the end
        TimerBar(unsigned timeout, int x, int y, int width, int height, GameScene* parent, SDL_Renderer* renderer);
        virtual ~TimerBar();
        void onDraw(SDL_Renderer* renderer);
        void onUpdate(const unsigned elapsedTime);
        void pause();
        void pause(bool flag);
        void resume();
        void start();
        void reset();
        void setEventCallback( TimeoutCallback callback );
        void setTimeout(unsigned timeout);
};

#endif // TIMERBAR_H
