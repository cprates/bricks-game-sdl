#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>

#include "Engine.h"
#include "MainMenuScene.h"
#include "GameScene.h"



class SceneManager
{
    public:
        void prepare(unsigned screenWidth, unsigned screenHeight, Engine* engine);
        void loadMainMenuScene();
        void loadGameScene(Level level);

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

        SceneManager();
        ~SceneManager();

        static SceneManager *instance;
        MainMenuScene* mainmenuScene;
        GameScene* gameScene;

};



#endif // SCENEMANAGER_H
