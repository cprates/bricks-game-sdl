#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Level.h"
#include "GameMatrix.h"
#include "Grid.h"
#include "TimerBar.h"


class GameScene : public Scene
{
    public:
        static const short BLOCK_WIDTH   = 40;    // pixels
        static const short BLOCK_HEIGHT  = 40;    // pixels
        static const short GRID_WIDTH  = 7;      // max n blocks
        static const short GRID_HEIGHT = 10;      // max n blocks
        static const unsigned GRID_X_POS  = 100;  // pixels
        static const unsigned GRID_Y_POS  = 110;  // pixels

        GameScene(Level level, SDL_Renderer* renderer);
        virtual ~GameScene();
        void gridClickEventCallback(int x, int y);
        void timerBarTimeoutCallback();
        void onUpdate(unsigned elapsedTime);

    private:
        GameMatrix logicMatrix;
        Grid graphicMatrix;
        TimerBar* timerBar;
        Level level;
        bool paused;

        void genLogicMatrix(Level* level);

};

#endif // GAMESCENE_H
