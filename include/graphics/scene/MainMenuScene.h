#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <SDL.h>

#include "LevelManager.h"
#include "Engine.h"
#include "Button.h"

class MainMenuSceneDummyData {};

class MainMenuScene : public Scene
{
    public:
        static const string BG_FILE_PATH;
        MainMenuScene(int width, int height, Engine* engine);
        virtual ~MainMenuScene();
        void onLoad();

    private:
        SDL_Renderer* renderer;
        Engine* engine;
        Button<MainMenuSceneDummyData, MainMenuScene>* muteButton;
        Button<MainMenuSceneDummyData, MainMenuScene>* playMusicButton;

        void buttonClickCallback(Entity* button, Level* level);
        void onPlayMusicCallback(Entity* button, MainMenuSceneDummyData* dd);
        void onMuteCallback(Entity* button, MainMenuSceneDummyData* dd);
};

#endif // MAINMENUSCENE_H
