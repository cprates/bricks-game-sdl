#include "GameScene.h"

GameScene::GameScene(Level* level, SDL_Renderer* renderer) :
    Scene(renderer),
    logicMatrix(GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT),
    graphicMatrix(GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, this, renderer)
{
    this->genLogicMatrix(level);
    this->graphicMatrix.build(&this->logicMatrix);
    this->graphicMatrix.setEventCallback( &GameScene::gridClickEventCallback );
    this->attachChild(&this->graphicMatrix);
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

void GameScene::gridClickEventCallback(int x, int y) {
    if(this->logicMatrix.isThere(x, y)) {
        vector<MatrixElement*> adjacentTwins;
        logicMatrix.getAdjacentTwins(x, y, &adjacentTwins);
        if(adjacentTwins.size() > 1) {
            // Estas duas linhas(logicMatrix.reallocElements() e graphicMatrix.build()) TEM DE FICAR
            // SEMPRE SEGUIDAS PORQUE O build() ACTUALIZA O Grid.matrixWidth. Se houver um realoc e este não for actualizado
            // as coordenadas dos clicks vao ficar desalinhadas
            cout << "Score: " << logicMatrix.reallocElements() << endl;
            this->graphicMatrix.build(&this->logicMatrix);
        }
        else if(adjacentTwins.size() > 0) {
            // restore element
            adjacentTwins[0]->toRemove = false;
        }
    }
}
