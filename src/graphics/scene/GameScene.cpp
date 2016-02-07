#include "GameScene.h"
#include "SceneManager.h"
#include "Button.h"
#include "Text.h"
#include "AlphaModifier.h"
#include "MoveYModifier.h"
#include "MoveXModifier.h"

const string GameScene::BACKGROUND_FILE_PATH = "resources/game_background.png";
const string GameScene::GAMEOVER_FILE_PATH = "resources/game_over.png";
const string GameScene::LEVELCOMPLETED_FILE_PATH = "resources/level_completed.png";
const string GameScene::TRUCK_FILE_PATH = "resources/truck.png";
const SDL_Color GameScene::LEVEL_TITLE_COLOUR = SDL_Color({200, 200, 200, 255});


GameScene::GameScene(Level level, Engine* engine, SDL_Renderer* renderer) :
    Scene(renderer, GAME_SCENE),
    logicMatrix(GRID_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT),
    graphicMatrix(GRID_START_X_POS, GRID_Y_POS, GRID_WIDTH, GRID_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, this, renderer),
    engine(engine),
    level(level),
    paused(true),
    gameOver(false),
    truckRunning(false),
    pauseButton(NULL),
    resumeButton(NULL),
    nextLevelButton(NULL),
    nextLevelOnGOButton(NULL),
    gameOverSprite(NULL),
    levelCompletedprite(NULL),
    truckSprite(NULL)
{
    Sprite* bg = new Sprite(BACKGROUND_FILE_PATH, 0, 0, engine->getScreenWidth(), engine->getScreenHeight(), renderer);
    attachChild(bg);

    int width  = 470;
    int height = 190;
    gameOverSprite = new Sprite(GAMEOVER_FILE_PATH,
        engine->getScreenWidth()/2 - width/2, engine->getScreenHeight()/2 - height/2, width, height, renderer);

    levelCompletedprite = new Sprite(LEVELCOMPLETED_FILE_PATH,
        engine->getScreenWidth()/2 - width/2, engine->getScreenHeight()/2 - height/2, width, height, renderer);

    levelTitle = new Text(level.getLevelTitle(), LEVEL_TITLE_COLOUR, 0, 0, LEVEL_TITLE_SIZE, engine);
    levelTitle->setPosition( engine->getScreenWidth()/2 - levelTitle->getRect()->w/2, LEVEL_TITLE_POSY );
    attachChild(levelTitle);
    //
    genLogicMatrix(&level);
    graphicMatrix.build(&this->logicMatrix);
    graphicMatrix.setEventCallback( &GameScene::gridClickEventCallback );
    graphicMatrix.setVisible(false);
    attachChild(&graphicMatrix);
    //
    truckSprite = new Sprite(TRUCK_FILE_PATH, 0, 0, 710, 640, renderer);
    attachChild(truckSprite);
    MoveXModifier<GameScene>* mx = new MoveXModifier<GameScene>(-800, 0, 3);
    mx->setCallback(&GameScene::truckStopCallback, this);
    truckSprite->addModifier(mx);
    truckSprite->setEnabled(false);
    truckRunning = true;

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
    detatchEntity(nextLevelButton);
    detatchEntity(nextLevelOnGOButton);
    detatchEntity(gameOverSprite);
    detatchEntity(levelCompletedprite);
    detatchEntity(levelTitle);
    detatchEntity(truckSprite);

    delete timerBar;
    delete scoreBar;
    delete pauseButton;
    delete resumeButton;
    delete nextLevelButton;
    delete nextLevelOnGOButton;
    delete gameOverSprite;
    delete levelCompletedprite;
    delete levelTitle;
    delete truckSprite;
}


void GameScene::initTimeBar() {
    SDL_Color colour({255, 0, 0});
    Text* label = new Text("New Cargo", colour, 450, 25, 20, engine, true);
    this->attachChild(label);

    this->timerBar = new TimerBar(level.getNewColumnTime(), 580, 20, 180, 30, this, renderer);
    this->timerBar->setEventCallback(&GameScene::timerBarTimeoutCallback);
    this->attachChild(this->timerBar);
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

    //TODO: need a resource manager...
    Button<DummyData, GameScene>* homeButton = new Button<DummyData, GameScene>
        ("resources/home_button.png", buttonX, 50, buttonWidth, buttonHeight, dm, this, renderer, true);
    homeButton->setClickCallback(&GameScene::buttonHomeCallback);
    attachChild(homeButton);

    Button<DummyData, GameScene>* resetButton = new Button<DummyData, GameScene>
        ("resources/restart_button.png", buttonX, 95, buttonWidth, buttonHeight, dm, this, renderer, true);
    resetButton->setClickCallback(&GameScene::buttonResetCallback);
    attachChild(resetButton);

    pauseButton = new Button<DummyData, GameScene>
        ("resources/pause_button.png", buttonX, 140, buttonWidth, buttonHeight, dm, this, renderer);
    pauseButton->setClickCallback(&GameScene::buttonPauseCallback);
    attachChild(pauseButton);

    resumeButton = new Button<DummyData, GameScene>
        ("resources/resume_button.png", buttonX, 140, buttonWidth, buttonHeight, dm, this, renderer);
    resumeButton->setClickCallback(&GameScene::buttonResumeCallback);
    resumeButton->setVisible(false);
    attachChild(resumeButton);

    Button<DummyData, GameScene>* pushgridButton = new Button<DummyData, GameScene>
        ("resources/pushgrid_button.png", buttonX, 185, buttonWidth, buttonHeight, dm, this, renderer, true);
    pushgridButton->setClickCallback(&GameScene::buttonPushGridCallback);
    attachChild(pushgridButton);

    nextLevelButton = new Button<DummyData, GameScene>
        ("resources/nextlevel_button.png", 400, 430, 100, 100, dm, this, renderer);
    nextLevelButton->setClickCallback(&GameScene::buttonNextLevelCallback);

    nextLevelOnGOButton = new Button<DummyData, GameScene>
        ("resources/restartgo_button.png", 400, 430, 100, 100, dm, this, renderer);
    nextLevelOnGOButton->setClickCallback(&GameScene::buttonResetCallback);
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
            ruler.incrementScore(score);
            graphicMatrix.build(&logicMatrix);
            scoreBar->incrementScore(score);

            if(ruler.levelCompleted(&level)) {
                onLevelCompleted();
            }
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
    ruler.reset();
    genLogicMatrix(&level);
    graphicMatrix.build(&logicMatrix);
    detatchEntity(gameOverSprite);
    detatchEntity(nextLevelOnGOButton);
    detatchEntity(levelCompletedprite);
    detatchEntity(nextLevelButton);
    paused = true;
    gameOver = false;
}


void GameScene::changeLevel(Level level) {
    this->level = level;
    reset();
    scoreBar->setMaxScore(level.getScoreToFinish());
    timerBar->setTimeout(level.getNewColumnTime());
    graphicMatrix.setVisible(true);
    pauseButton->setVisible(true);
    resumeButton->setVisible(false);

    delete levelTitle;
    levelTitle = new Text(level.getLevelTitle(), LEVEL_TITLE_COLOUR, 0, 0, LEVEL_TITLE_SIZE, engine);
    levelTitle->setPosition( engine->getScreenWidth()/2 - levelTitle->getRect()->w/2, LEVEL_TITLE_POSY );
    attachChild(levelTitle);

    //
    graphicMatrix.setPosition(GRID_START_X_POS, GRID_Y_POS);
    graphicMatrix.setVisible(false);
    MoveXModifier<GameScene>* mx = new MoveXModifier<GameScene>(-800, 0, 2);
    mx->setCallback(&GameScene::truckStopCallback, this);
    truckSprite->addModifier(mx);
    truckSprite->setEnabled(false);
    truckRunning = true;
}

void GameScene::onGameOver() {
    timerBar->pause();
    gameOver = true;
    gameOverSprite->addModifier(new AlphaModifier(0, 255, 0.3));
    attachChild(gameOverSprite);
    nextLevelOnGOButton->addModifier(new AlphaModifier(0, 255, 0.3));
    attachChild(nextLevelOnGOButton);
}

void GameScene::onLevelCompleted() {
    timerBar->pause();
    gameOver = true;
    levelCompletedprite->addModifier(new AlphaModifier(0, 255, 0.5));
    attachChild(levelCompletedprite);
    // is it the last one?!
    if(level.getLevelID() < LevelManager::getInstance()->countLevels()) {
        nextLevelButton->addModifier(new AlphaModifier(0, 255, 0.5));
        attachChild(nextLevelButton);
    }
}

void GameScene::buttonResetCallback(Entity* button, DummyData* dm) {
    if(!truckRunning)
        changeLevel(level);
}

void GameScene::buttonHomeCallback(Entity* button, DummyData* dm) {
    SceneManager::getInstance()->loadLoadingScene(MAINMENU_SCENE);
}

void GameScene::buttonPushGridCallback(Entity* button, DummyData* dm) {
    if(!paused && !gameOver) {
        timerBarTimeoutCallback();
        timerBar->start();
    }
    if(gameOver) {
        timerBar->pause();
    }
}

void GameScene::buttonPauseCallback(Entity* button, DummyData* dm) {
    if(!gameOver && !paused) {
        paused = !paused;
        timerBar->pause(paused);
        button->setVisible(false);
        resumeButton->setVisible(true);
        graphicMatrix.setEnabled(false);
        graphicMatrix.addModifier(new AlphaModifier(255, 0, 0.2));
    }
}

void GameScene::buttonResumeCallback(Entity* button, DummyData* dm) {
    if(!gameOver) {
        paused = !paused;
        timerBar->pause(paused);
        button->setVisible(false);
        pauseButton->setVisible(true);
        graphicMatrix.setEnabled(true);
        graphicMatrix.addModifier(new AlphaModifier(0, 255, 0.2));
    }
}

void GameScene::buttonNextLevelCallback(Entity* button, DummyData* dm) {
    Level* _level = LevelManager::getInstance()->getLevel(level.getLevelID() + 1);
    SceneManager::getInstance()->loadLoadingScene(GAME_SCENE, _level);
}

void GameScene::truckStopCallback() {
    MoveXModifier<GameScene>* mx = new MoveXModifier<GameScene>(GRID_START_X_POS, GRID_X_POS, 1.5);
    mx->setCallback(&GameScene::gridStopCallback, this);
    graphicMatrix.addModifier(mx);
    graphicMatrix.setVisible(true);
}

void GameScene::gridStopCallback() {
    timerBar->start();
    paused = false;
    truckRunning = false;
}
