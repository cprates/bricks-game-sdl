#ifndef SCOREBAR_H
#define SCOREBAR_H

#include "Sprite.h"

class ScoreBar : public Sprite
{
    int score;
    float maxScore;
    float _ratio;  // time VS shaft width
    Sprite* timerBarShaft;
    unsigned shaftMaxWidth;

    public:
        static const string TIMERBAR_FRAME_FILE_PATH;
        static const string TIMERBAR_SHAFT_FILE_PATH;
        static const short FRAME_BORDER = 3; // pixels

        ScoreBar(float maxScore, int x, int y, int width, int height, SDL_Renderer* renderer);
        virtual ~ScoreBar();
        void onDraw(SDL_Renderer* renderer);
        void incrementScore(int score);
        void reset();
};

#endif // SCOREBAR_H
