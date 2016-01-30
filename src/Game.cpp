
#include <string>
#include <iostream>

#include "GameMatrix.h"
#include "Engine.h"
#include "GameScene.h"

using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;
const string GAME_TITLE = "Cube Crush";

int main( int argc, char* args[] ) {
    Engine engine (SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    GameScene scene;
    if(!engine.init()) return -1;


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
