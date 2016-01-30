
#include <string>
#include <iostream>

#include "GameMatrix.h"
#include "Engine.h"
#include "GameScene.h"
#include "Sprite.h"

using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;
const string GAME_TITLE = "Cube Crush";

int main( int argc, char* args[] ) {
    Engine engine (SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    GameScene scene;
    if(!engine.init()) return -1;

    Sprite et1(0, 0, 320, 240);
    Sprite* et2 = new Sprite(100, 100, 200, 200, true);
    Sprite* et3 = new Sprite(350, 200, 120, 100, true);

    et3->setAngle(45);

    et2->create("sprite.bmp", engine.getRenderer());
    et3->create("sprite.bmp", engine.getRenderer());

    scene.attachChild(&et1);
    scene.attachChild(et2);
    scene.attachChild(et3);

    scene.detatchEntity(&et1);

    engine.setScene(&scene);
    engine.start();

    GameMatrix *gm = new GameMatrix(0, 0, 10, 10);

    gm->genColumn(6);
    gm->genColumn(6);
    gm->genColumn(6);
    //gm->getElement(1, 4)->getColour()->print();
    vector<MatrixElement*> adjacentTwins;
    gm->getAdjacentTwins(1, 5, &adjacentTwins);

    gm->print();
    cout << "Score: " << gm->reallocElements() << endl;
    cout << endl << endl;
    gm->print();
    delete gm;

    return 0;
}
