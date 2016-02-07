#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Engine.h"
#include "Ruler.h"
#include "GameMatrix.h"
#include "Grid.h"
#include "TimerBar.h"
#include "ScoreBar.h"
#include "Button.h"
#include "Text.h"

class DummyData {};

class GameScene : public Scene
{
    public:
        static const string BACKGROUND_FILE_PATH;
        static const string GAMEOVER_FILE_PATH;
        static const string LEVELCOMPLETED_FILE_PATH;
        static const string TRUCK_FILE_PATH;
        //
        static const SDL_Color LEVEL_TITLE_COLOUR;
        static const short LEVEL_TITLE_SIZE = 30;
        static const int LEVEL_TITLE_POSY = 70;
        //
        static const short BLOCK_WIDTH    = 40;   // pixels
        static const short BLOCK_HEIGHT   = 40;   // pixels
        static const short GRID_WIDTH     = 15;   // max n blocks
        static const short GRID_HEIGHT    = 9;    // max n blocks
        static const unsigned GRID_X_POS  = 100;  // pixels
        static const unsigned GRID_START_X_POS  = -500;  // pixels
        static const unsigned GRID_Y_POS  = 160;  // pixels

        GameScene(Level level, Engine* engine, SDL_Renderer* renderer);
        virtual ~GameScene();
        void gridClickEventCallback(int x, int y);
        void timerBarTimeoutCallback();
        void onUpdate(unsigned elapsedTime);
        void reset();
        void changeLevel(Level level);

    private:
        GameMatrix logicMatrix;
        Grid graphicMatrix;
        TimerBar* timerBar;
        ScoreBar* scoreBar;
        Engine* engine;
        Level level;
        Ruler ruler;
        bool paused;
        bool gameOver;
        bool truckRunning;
        Button<DummyData, GameScene>* pauseButton;
        Button<DummyData, GameScene>* resumeButton;
        Button<DummyData, GameScene>* nextLevelButton;
        Button<DummyData, GameScene>* nextLevelOnGOButton;
        Sprite* gameOverSprite;
        Sprite* levelCompletedprite;
        Text* levelTitle;
        Sprite* truckSprite;

        void initTimeBar();
        void initScoreBar();
        void setButtons();
        void genLogicMatrix(Level* level);
        void onGameOver();
        void onLevelCompleted();
        void buttonResetCallback(Entity* button, DummyData* dm);
        void buttonHomeCallback(Entity* button, DummyData* dm);
        void buttonPushGridCallback(Entity* button, DummyData* dm);
        void buttonPauseCallback(Entity* button, DummyData* dm);
        void buttonResumeCallback(Entity* button, DummyData* dm);
        void buttonNextLevelCallback(Entity* button, DummyData* dm);
        void truckStopCallback();
        void gridStopCallback();

};

#endif // GAMESCENE_H
