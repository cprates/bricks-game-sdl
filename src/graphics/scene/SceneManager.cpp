#include "SceneManager.h"

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager() :
    engine(NULL),
    nextScene(0),
    mainmenuScene(NULL),
    gameScene(NULL)
{

}

SceneManager::~SceneManager()
{
    engine->setScene(NULL);
    engine->setSubScene(NULL);
    engine->setIOListener(NULL);

    delete gameScene;
    delete mainmenuScene;
    delete loadingScene;
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

void SceneManager::loadGameScene() {
    if(gameScene == NULL) {
        gameScene = new GameScene(*level, engine, engine->getRenderer());
    }
    else {
        gameScene->changeLevel(*level);
    }

    engine->setScene(gameScene);
    engine->setIOListener(gameScene);
}


void SceneManager::loadLoadingScene(int nextScene) {
    if(loadingScene == NULL)
        loadingScene = new LoadingScene(engine, engine->getRenderer());

    engine->setSubScene(loadingScene);
    loadingScene->show();
    this->nextScene = nextScene;
}


void SceneManager::loadLoadingScene(int nextScene, Level* level) {
    if(loadingScene == NULL)
        loadingScene = new LoadingScene(engine, engine->getRenderer());

    engine->setSubScene(loadingScene);
    loadingScene->show();
    this->nextScene = nextScene;
    this->level = level;
}

void SceneManager::changeScene() {
    if(nextScene == MAINMENU_SCENE) {
        this->loadMainMenuScene();
    }
    else if(nextScene == GAME_SCENE) {
        this->loadGameScene();
    }
}

void SceneManager::detachLoadingScene() {
    engine->detachSubScene();
}
