#include "GameScene.h"

GameScene::GameScene(Level* level, SDL_Renderer* renderer) :
    Scene(renderer),
    logicMatrix(GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT),
    graphicMatrix(GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, renderer)
{
    this->genLogicMatrix(level);
    this->graphicMatrix.build(&this->logicMatrix);
    this->attachChild(&this->graphicMatrix);


    /*
    vector<MatrixElement*> adjacentTwins;
    logicMatrix.getAdjacentTwins(4, 3, &adjacentTwins);
    cout << "Score: " << logicMatrix.reallocElements() << endl;
    this->graphicMatrix.build(&this->logicMatrix);
    */
}

GameScene::~GameScene()
{
    //dtor
}


void GameScene::genLogicMatrix(Level* level) {
    short cols = level->getMatrixCols();
    short nColours = level->getNColours();
    for(int i = 0; i < cols; i++) {
        this->logicMatrix.genColumn(nColours);
    }
}
