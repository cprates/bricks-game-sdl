#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#define MAINMENU_SCENE        0
#define GAME_SCENE            1
#define LOADING_SCENE         2

#include <iostream>

#include "Engine.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "LoadingScene.h"


class SceneManager
{
    public:
        void prepare(unsigned screenWidth, unsigned screenHeight, Engine* engine);
        void loadMainMenuScene();
        void loadGameScene();
        void loadLoadingScene(int nextScene);
        void loadLoadingScene(int nextScene, Level* level);
        void changeScene();
        void detachLoadingScene();
        void close();

        static SceneManager* getInstance()
        {
            if(instance == NULL) {
                instance = new SceneManager;
            }
            return instance;
        }

    private:
        unsigned screenWidth;
        unsigned screenHeight;
        Engine* engine;
        int nextScene;
        Level* level;

        SceneManager();
        ~SceneManager();

        static SceneManager* instance;
        MainMenuScene* mainmenuScene;
        GameScene* gameScene;
        LoadingScene* loadingScene;

};



#endif // SCENEMANAGER_H
