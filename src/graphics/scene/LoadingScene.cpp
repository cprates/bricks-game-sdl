#include "LoadingScene.h"
#include "MoveXModifier.h"
#include "SceneManager.h"

const string LoadingScene::FROMLEFT_FILE_PATH = "resources/fromleft.png";
const string LoadingScene::FROMRIGHT_FILE_PATH = "resources/fromright.png";
const float LoadingScene::DURATION = 0.8;
const float LoadingScene::HIDE_TIME = 1000;
const float LoadingScene::DONE_TIME = 2000;

LoadingScene::LoadingScene(Engine* engine, SDL_Renderer* renderer) :
    Scene(renderer, LOADING_SCENE),
    step(0),
    counter(0)
{
    fromLeftSprite = new Sprite(FROMLEFT_FILE_PATH, -500, 0, 500, 680, renderer);
    attachChild(fromLeftSprite);
    fromRightSprite = new Sprite(FROMRIGHT_FILE_PATH, 900, 0, 500, 680, renderer);
    attachChild(fromRightSprite);
}

LoadingScene::~LoadingScene()
{
    detatchEntity(fromLeftSprite);
    detatchEntity(fromRightSprite);

    delete fromLeftSprite;
    delete fromRightSprite;
}

void LoadingScene::show() {
    fromLeftSprite->clearModifiers();
    fromRightSprite->clearModifiers();
    fromLeftSprite->addModifier(new MoveXModifier<LoadingScene>(-500, 0, DURATION));
    fromRightSprite->addModifier(new MoveXModifier<LoadingScene>(900, 400, DURATION));
    counter = 0;
    step = 0;
}

void LoadingScene::hide() {
    fromLeftSprite->addModifier(new MoveXModifier<LoadingScene>(0, -500, DURATION));
    fromRightSprite->addModifier(new MoveXModifier<LoadingScene>(400, 900, DURATION));

    SceneManager::getInstance()->changeScene();
}

void LoadingScene::done() {
    SceneManager::getInstance()->detachLoadingScene();
}

void LoadingScene::onUpdate(unsigned elapsedTime) {
    Scene::onUpdate(elapsedTime);
    counter += elapsedTime;
    if(counter >= DONE_TIME && step == 1) {
        step++;
        done();
    }
    else if(counter >= HIDE_TIME && step == 0) {
        step++;
        hide();
    }
}
