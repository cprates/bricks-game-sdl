#include "SceneManager.h"

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager() :
    engine(NULL),
    mainmenuScene(NULL),
    gameScene(NULL)
{

}

SceneManager::~SceneManager()
{
    engine->setScene(NULL);
    engine->setIOListener(NULL);

    delete gameScene;
    delete mainmenuScene;
}


void SceneManager::prepare(unsigned screenWidth, unsigned screenHeight, Engine* engine) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->engine = engine;
}

void SceneManager::loadMainMenuScene() {
    if(mainmenuScene == NULL) {
        mainmenuScene = new MainMenuScene(screenWidth, screenHeight, engine->getRenderer());
    }

    engine->setIOListener(mainmenuScene);
    engine->setScene(mainmenuScene);
}

void SceneManager::loadGameScene(Level level) {
    if(gameScene == NULL) {
        gameScene = new GameScene(level, engine, engine->getRenderer());
    }
    else {
        gameScene->changeLevel(level);
    }

    engine->setScene(gameScene);
    engine->setIOListener(gameScene);
}
