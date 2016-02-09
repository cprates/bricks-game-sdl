#include "MainMenuScene.h"
#include "SceneManager.h"
#include "Button.h"
#include "SoundManager.h"

#include <iostream>

const string MainMenuScene::BG_FILE_PATH = "resources/mainmenu_background.png";

MainMenuScene::MainMenuScene(int width, int height, Engine* engine) :
    Scene(renderer, MAINMENU_SCENE),
    renderer(engine->getRenderer()),
    engine(engine)
{
    Sprite* bg = new Sprite(BG_FILE_PATH, 0, 0,width, height, renderer, true);
    attachChild(bg);

    Level* level = LevelManager::getInstance()->getLevel(1);
    Button<Level, MainMenuScene>* firstLevelButton = new Button<Level, MainMenuScene>
        ("resources/firstLevelButton.png", 220, 520, 55, 70, *level, this, renderer, true);
    firstLevelButton->setClickCallback(&MainMenuScene::buttonClickCallback);
    attachChild(firstLevelButton);

    level = LevelManager::getInstance()->getLevel(2);
    Button<Level, MainMenuScene>* secondLevelButton = new Button<Level, MainMenuScene>
        ("resources/secondLevelButton.png", 650, 250, 55, 70, *level, this, renderer, true);
    secondLevelButton->setClickCallback(&MainMenuScene::buttonClickCallback);
    attachChild(secondLevelButton);

    level = LevelManager::getInstance()->getLevel(3);
    Button<Level, MainMenuScene>* thirdLevelButton = new Button<Level, MainMenuScene>
        ("resources/thirdLevelButton.png", 515, 20, 55, 70, *level, this, renderer, true);
    thirdLevelButton->setClickCallback(&MainMenuScene::buttonClickCallback);
    attachChild(thirdLevelButton);


    // sound
    MainMenuSceneDummyData dd;
    muteButton = new Button<MainMenuSceneDummyData, MainMenuScene>
        ("resources/mute.png", 0, 0, 25, 25, dd, this, renderer);
    muteButton->setPosition(engine->getScreenWidth() - muteButton->getRect()->w - 5, 5);
    muteButton->setClickCallback(&MainMenuScene::onPlayMusicCallback);
    muteButton->setVisible(false);
    attachChild(muteButton);

    playMusicButton = new Button<MainMenuSceneDummyData, MainMenuScene>
        ("resources/nomute.png", 0, 0, 25, 25, dd, this, renderer);
    playMusicButton->setPosition(engine->getScreenWidth() - playMusicButton->getRect()->w - 5, 5);
    playMusicButton->setClickCallback(&MainMenuScene::onMuteCallback);
    attachChild(playMusicButton);


    SoundManager::getInstance()->playMusic();
}

MainMenuScene::~MainMenuScene()
{
    detatchEntity(muteButton);
    detatchEntity(playMusicButton);

    delete muteButton;
    delete playMusicButton;
}

void MainMenuScene::onLoad() {
    bool onMute = SoundManager::getInstance()->isOnMute();
    muteButton->setVisible(onMute);
    playMusicButton->setVisible(!onMute);
}

void MainMenuScene::buttonClickCallback(Entity* button, Level* level) {
    SceneManager::getInstance()->loadLoadingScene(GAME_SCENE, level);
    SoundManager::getInstance()->playClick();
}

void MainMenuScene::onMuteCallback(Entity* button, MainMenuSceneDummyData* dd) {
    muteButton->setVisible(true);
    playMusicButton->setVisible(false);
    SoundManager::getInstance()->setMute(true);
    SoundManager::getInstance()->pauseMusic();
}

void MainMenuScene::onPlayMusicCallback(Entity* button, MainMenuSceneDummyData* dd) {
    muteButton->setVisible(false);
    playMusicButton->setVisible(true);
    SoundManager::getInstance()->setMute(false);
    SoundManager::getInstance()->resumeMusic();
}
