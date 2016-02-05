#include "MainMenuScene.h"
#include "SceneManager.h"
#include "Button.h"


const string MainMenuScene::BG_FILE_PATH = "resources/mainmenu_background.png";

MainMenuScene::MainMenuScene(int width, int height, SDL_Renderer* renderer) :
    Scene(renderer),
    renderer(renderer)
{
    Sprite* bg = new Sprite(BG_FILE_PATH, 0, 0,width, height, renderer, true);
    attachChild(bg);

    Level* level = LevelManager::getInstance()->getLevel(1);
    Button<Level, MainMenuScene>* firstLevelButton = new Button<Level, MainMenuScene>
        ("resources/firstLevelButton.png", 250, 500, 70, 70, *level, this, renderer, true);
    firstLevelButton->setClickCallback(&MainMenuScene::buttonClickCallback);
    attachChild(firstLevelButton);

    level = LevelManager::getInstance()->getLevel(2);
    Button<Level, MainMenuScene>* secondLevelButton = new Button<Level, MainMenuScene>
        ("resources/secondLevelButton.png", 690, 250, 70, 70, *level, this, renderer, true);
    secondLevelButton->setClickCallback(&MainMenuScene::buttonClickCallback);
    attachChild(secondLevelButton);
}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::buttonClickCallback(Entity* button, Level* level) {
    SceneManager::getInstance()->loadGameScene(*level);
}
