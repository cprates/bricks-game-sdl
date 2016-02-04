
#include <string>
#include <iostream>

#include "GameMatrix.h"
#include "Engine.h"
#include "Scene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "FirstLevel.h"

using namespace std;


const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 640;
const string GAME_TITLE = "Cube Crush";

int main( int argc, char* args[] ) {
    Engine engine (SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    if(!engine.init()) return -1;

    FirstLevel firstLevel;
    //GameScene scene(firstLevel, engine.getRenderer());
    MainMenuScene scene(SCREEN_WIDTH, SCREEN_HEIGHT, engine.getRenderer());
    engine.setIOListener(&scene);
    engine.setScene(&scene);
    engine.start();

    return 0;
}
