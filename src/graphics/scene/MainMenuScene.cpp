#include "MainMenuScene.h"
#include "SceneManager.h"



const string MainMenuScene::BG_FILE_PATH = "mainmenu_background.png";

MainMenuScene::MainMenuScene(int width, int height, SDL_Renderer* renderer) :
    Scene(renderer),
    renderer(renderer)
{
    Sprite* bg = new Sprite(BG_FILE_PATH, 0, 0,width, height, renderer, true);
    attachChild(bg);

    FirstLevel level;
    Button<Level, MainMenuScene>* firstLevelButton = new Button<Level, MainMenuScene>
        ("firstLevelButton.png", 150, 500, 70, 70, level, this, renderer, true);
    firstLevelButton->setClickCallback(&MainMenuScene::buttonClickCallback);
    attachChild(firstLevelButton);

    SecondLevel level2;
    Button<Level, MainMenuScene>* secondLevelButton = new Button<Level, MainMenuScene>
        ("secondLevelButton.png", 280, 350, 70, 70, level2, this, renderer, true);
    secondLevelButton->setClickCallback(&MainMenuScene::buttonClickCallback);
    attachChild(secondLevelButton);
}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::buttonClickCallback(Level* level) {
    SceneManager::getInstance()->loadGameScene(*level);
}
