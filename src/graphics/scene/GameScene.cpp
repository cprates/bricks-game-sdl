#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene(Level level, Engine* engine, SDL_Renderer* renderer) :
    Scene(renderer),
    logicMatrix(GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT),
    graphicMatrix(GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, this, renderer),
    engine(engine),
    level(level),
    paused(false)
{
    this->genLogicMatrix(&level);
    this->graphicMatrix.build(&this->logicMatrix);
    this->graphicMatrix.setEventCallback( &GameScene::gridClickEventCallback );
    this->attachChild(&this->graphicMatrix);

    //timerbar init
    this->timerBar = new TimerBar(level.getNewColumnTime(), 400, 50, 180, 30, this, renderer);
    this->timerBar->setEventCallback(&GameScene::timerBarTimeoutCallback);
    this->attachChild(this->timerBar);
    this->timerBar->start();
    //scorebar init
    this->scoreBar = new ScoreBar(level.getScoreToFinish(), 100, 50, 180, 30, renderer);
    this->attachChild(this->scoreBar);

    // buttons
    DummyData dm;
    Button<DummyData, GameScene>* resetButton = new Button<DummyData, GameScene>
        ("restart_button.png", 750, 400, 40, 40, dm, this, renderer, true);
    resetButton->setClickCallback(&GameScene::buttonResetCallback);
    attachChild(resetButton);

    Button<DummyData, GameScene>* homeButton = new Button<DummyData, GameScene>
        ("home_button.png", 750, 480, 40, 40, dm, this, renderer, true);
    homeButton->setClickCallback(&GameScene::buttonHomeCallback);
    attachChild(homeButton);
}

GameScene::~GameScene()
{
    detatchEntity(timerBar);
    detatchEntity(&graphicMatrix);
    detatchEntity(scoreBar);

    delete this->timerBar;
    delete this->scoreBar;
}


void GameScene::genLogicMatrix(Level* level) {
    short cols = level->getMatrixCols();
    short nColours = level->getNColours();
    cout << "Antes" << endl;
    this->logicMatrix.clean();

    for(int i = 0; i < cols; i++) {
        this->logicMatrix.genColumn(nColours);
    }
    cout << "Depois" << endl;
}

void GameScene::gridClickEventCallback(int x, int y) {
    if(this->logicMatrix.isThere(x, y) && !paused) {
        vector<MatrixElement*> adjacentTwins;
        logicMatrix.getAdjacentTwins(x, y, &adjacentTwins);
        if(adjacentTwins.size() > 1) {
            // Estas duas linhas(logicMatrix.reallocElements() e graphicMatrix.build()) TEM DE FICAR
            // SEMPRE SEGUIDAS PORQUE O build() ACTUALIZA O Grid.matrixWidth. Se houver um realoc e este não for actualizado
            // as coordenadas dos clicks vao ficar desalinhadas
            int score = logicMatrix.reallocElements();
            cout << "Score: " << score << endl;
            graphicMatrix.build(&logicMatrix);
            scoreBar->incrementScore(score);
        }
        else if(adjacentTwins.size() > 0) {
            // restore element
            adjacentTwins[0]->toRemove = false;
        }
    }
}

void GameScene::timerBarTimeoutCallback() {
    if(logicMatrix.getWidth() < GRID_WIDTH) {
        this->logicMatrix.genColumn(this->level.getNColours());
        this->graphicMatrix.build(&this->logicMatrix);
    }
    else {
        //TODO: show score or something like that
        this->timerBar->pause();
        this->paused = true;
        cout << "Game Over!!" << endl;
    }

}

void GameScene::onUpdate(unsigned elapsedTime) {
    Scene::onUpdate(elapsedTime);
}

void GameScene::reset() {
    timerBar->reset();
    scoreBar->reset();
    this->genLogicMatrix(&level);
    this->graphicMatrix.build(&this->logicMatrix);
    paused = false;
}

void GameScene::changeLevel(Level level) {
    this->level = level;
    reset();
    timerBar->resume();
}

void GameScene::buttonResetCallback(DummyData* dm) {
    reset();
    timerBar->resume();
}

void GameScene::buttonHomeCallback(DummyData* dm) {
    SceneManager::getInstance()->loadMainMenuScene();
}


