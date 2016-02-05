#include "GameScene.h"
#include "SceneManager.h"
#include "Button.h"
#include "Text.h"
#include "AlphaModifier.h"
#include "MoveYModifier.h"

const string GameScene::GAMEOVER_FILE_PATH = "resources/game_over.png";

GameScene::GameScene(Level level, Engine* engine, SDL_Renderer* renderer) :
    Scene(renderer),
    logicMatrix(GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT),
    graphicMatrix(GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, this, renderer),
    engine(engine),
    level(level),
    paused(false),
    gameOver(false),
    pauseButton(NULL),
    resumeButton(NULL),
    gameOverSprite(NULL)
{
    int width  = 480;
    int height = 180;
    gameOverSprite = new Sprite(GAMEOVER_FILE_PATH,
    engine->getScreenWidth()/2 - width/2, engine->getScreenHeight()/2 - height/2, width, height, renderer);

    this->genLogicMatrix(&level);
    this->graphicMatrix.build(&this->logicMatrix);
    this->graphicMatrix.setEventCallback( &GameScene::gridClickEventCallback );
    this->attachChild(&this->graphicMatrix);

    initTimeBar();
    initScoreBar();
    setButtons();
}

GameScene::~GameScene()
{
    detatchEntity(timerBar);
    detatchEntity(&graphicMatrix);
    detatchEntity(scoreBar);
    detatchEntity(pauseButton);
    detatchEntity(resumeButton);

    delete this->timerBar;
    delete this->scoreBar;
    delete this->pauseButton;
    delete this->resumeButton;
}


void GameScene::initTimeBar() {
    SDL_Color colour({255, 0, 0});
    Text* label = new Text("New Cargo", colour, 450, 25, 20, engine, true);
    this->attachChild(label);

    this->timerBar = new TimerBar(level.getNewColumnTime(), 580, 20, 180, 30, this, renderer);
    this->timerBar->setEventCallback(&GameScene::timerBarTimeoutCallback);
    this->attachChild(this->timerBar);
    this->timerBar->start();
}

void GameScene::initScoreBar() {
    SDL_Color colour({0, 150, 0});
    Text* label = new Text("Score", colour, 150, 25, 20, engine, true);
    this->attachChild(label);

    this->scoreBar = new ScoreBar(level.getScoreToFinish(), 230, 20, 180, 30, renderer);
    this->attachChild(this->scoreBar);
}

void GameScene::setButtons() {
    // buttons
    DummyData dm;
    short buttonWidth = 35;
    short buttonHeight = 35;
    unsigned buttonX = 820;

    Button<DummyData, GameScene>* homeButton = new Button<DummyData, GameScene>
        ("home_button.png", buttonX, 50, buttonWidth, buttonHeight, dm, this, renderer, true);
    homeButton->setClickCallback(&GameScene::buttonHomeCallback);
    attachChild(homeButton);

    Button<DummyData, GameScene>* resetButton = new Button<DummyData, GameScene>
        ("restart_button.png", buttonX, 95, buttonWidth, buttonHeight, dm, this, renderer, true);
    resetButton->setClickCallback(&GameScene::buttonResetCallback);
    attachChild(resetButton);

    pauseButton = new Button<DummyData, GameScene>
        ("pause_button.png", buttonX, 140, buttonWidth, buttonHeight, dm, this, renderer);
    pauseButton->setClickCallback(&GameScene::buttonPauseCallback);
    attachChild(pauseButton);

    resumeButton = new Button<DummyData, GameScene>
        ("resume_button.png", buttonX, 140, buttonWidth, buttonHeight, dm, this, renderer);
    resumeButton->setClickCallback(&GameScene::buttonResumeCallback);
    resumeButton->setVisible(false);
    attachChild(resumeButton);

    Button<DummyData, GameScene>* pushgridButton = new Button<DummyData, GameScene>
        ("pushgrid_button.png", buttonX, 185, buttonWidth, buttonHeight, dm, this, renderer, true);
    pushgridButton->setClickCallback(&GameScene::buttonPushGridCallback);
    attachChild(pushgridButton);
}

void GameScene::genLogicMatrix(Level* level) {
    short cols = level->getMatrixCols();
    short nColours = level->getNColours();
    this->logicMatrix.clean();

    for(int i = 0; i < cols; i++) {
        this->logicMatrix.genColumn(nColours);
    }
}

void GameScene::gridClickEventCallback(int x, int y) {
    if(this->logicMatrix.isThere(x, y) && !paused && !gameOver) {
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
        onGameOver();
    }

}

void GameScene::onUpdate(unsigned elapsedTime) {
    Scene::onUpdate(elapsedTime);
}

void GameScene::reset() {
    timerBar->reset();
    scoreBar->reset();
    genLogicMatrix(&level);
    graphicMatrix.build(&this->logicMatrix);
    detatchEntity(gameOverSprite);
    paused = false;
    gameOver = false;
}

void GameScene::changeLevel(Level level) {
    this->level = level;
    reset();
    scoreBar->setMaxScore(level.getScoreToFinish());
    timerBar->setTimeout(level.getNewColumnTime());
    timerBar->resume();
    graphicMatrix.setVisible(true);
    pauseButton->setVisible(true);
    resumeButton->setVisible(false);
}

void GameScene::onGameOver() {
    timerBar->pause();
    gameOver = true;
    gameOverSprite->addModifier(new AlphaModifier(0, 255, 0.3));
    attachChild(gameOverSprite);
}

void GameScene::buttonResetCallback(Entity* button, DummyData* dm) {
    changeLevel(level);
}

void GameScene::buttonHomeCallback(Entity* button, DummyData* dm) {
    SceneManager::getInstance()->loadMainMenuScene();
}

void GameScene::buttonPushGridCallback(Entity* button, DummyData* dm) {
    if(!paused && !gameOver) {
        timerBarTimeoutCallback();
    }
}

void GameScene::buttonPauseCallback(Entity* button, DummyData* dm) {
    if(!gameOver) {
        paused = !paused;
        timerBar->pause(paused);
        button->setVisible(false);
        resumeButton->setVisible(true);
        graphicMatrix.setVisible(false);
    }
}

void GameScene::buttonResumeCallback(Entity* button, DummyData* dm) {
    if(!gameOver) {
        paused = !paused;
        timerBar->pause(paused);
        button->setVisible(false);
        pauseButton->setVisible(true);
        graphicMatrix.setVisible(true);
    }
}


