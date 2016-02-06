#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <SDL.h>

#include "LevelManager.h"
#include "Engine.h"
#include "Button.h"


class MainMenuScene : public Scene
{
    public:
        MainMenuScene(int width, int height, SDL_Renderer* renderer);
        virtual ~MainMenuScene();

    private:
        static const string BG_FILE_PATH;
        SDL_Renderer* renderer;
        Engine* engine;

        void buttonClickCallback(Entity* button, Level* level);
};

#endif // MAINMENUSCENE_H