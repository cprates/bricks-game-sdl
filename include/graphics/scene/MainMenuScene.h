#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <SDL.h>

#include "Level.h"
#include "FirstLevel.h"
#include "SecondLevel.h"
#include "Scene.h"
#include "Button.h"


class MainMenuScene : public Scene
{
    public:
        MainMenuScene(int width, int height, SDL_Renderer* renderer);
        virtual ~MainMenuScene();

    private:
        static const string BG_FILE_PATH;
        SDL_Renderer* renderer;

        void buttonClickCallback(Level* level);
};

#endif // MAINMENUSCENE_H
