
#include <string>
#include <iostream>

#include "GameMatrix.h"
#include "Engine.h"
#include "SceneManager.h"

using namespace std;


static const unsigned SCREEN_WIDTH = 900;
static const unsigned SCREEN_HEIGHT = 640;
static const string GAME_TITLE = "Cube Crush";

int main( int argc, char* args[] ) {
    Engine engine (SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    if(!engine.init()) return -1;

    SceneManager::getInstance()->prepare(SCREEN_WIDTH, SCREEN_HEIGHT, &engine);
    SceneManager::getInstance()->loadMainMenuScene();
    engine.start();

    return 0;
}
