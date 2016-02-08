#include "SoundManager.h"
#include <stdexcept>

#include <iostream>
using namespace std;

SoundManager* SoundManager::instance = NULL;
const std::string SoundManager::MUSIC_FILE_PATH = "resources/sound/music.ogg";
const std::string SoundManager::CLICK_FILE_PATH = "resources/sound/click.ogg";
const std::string SoundManager::CRUSH_FILE_PATH = "resources/sound/block_crush.ogg";
const std::string SoundManager::GAMEOVER_FILE_PATH = "resources/sound/game_over.ogg";
const std::string SoundManager::LEVEL_COMPLETED_FILE_PATH = "resources/sound/level_completed.ogg";

SoundManager::SoundManager() :
    music(NULL),
    click(NULL),
    crush(NULL),
    gameOver(NULL),
    levelCompleted(NULL),
    onMute(false)
{
    loadMusic();
}

void SoundManager::close() {
    Mix_FreeMusic(music);
    //
    Mix_FreeChunk(click);
    Mix_FreeChunk(crush);
    Mix_FreeChunk(gameOver);
    Mix_FreeChunk(levelCompleted);

    Mix_HaltMusic();
}

void SoundManager::loadMusic() {
    music = Mix_LoadMUS(MUSIC_FILE_PATH.c_str());
    if(music == NULL) {
        throw std::runtime_error("!!! Error loading music file: " + MUSIC_FILE_PATH);
    }

    click = Mix_LoadWAV(CLICK_FILE_PATH.c_str());
    if(click == NULL) {
        throw std::runtime_error("!!! Error loading sound file: " + CLICK_FILE_PATH);
    }

    crush = Mix_LoadWAV(CRUSH_FILE_PATH.c_str());
    if(crush == NULL) {
        throw std::runtime_error("!!! Error loading sound file: " + CRUSH_FILE_PATH);
    }

    gameOver = Mix_LoadWAV(GAMEOVER_FILE_PATH.c_str());
    if(gameOver == NULL) {
        throw std::runtime_error("!!! Error loading sound file: " + GAMEOVER_FILE_PATH);
    }

    levelCompleted = Mix_LoadWAV(LEVEL_COMPLETED_FILE_PATH.c_str());
    if(levelCompleted == NULL) {
        throw std::runtime_error("!!! Error loading sound file: " + LEVEL_COMPLETED_FILE_PATH);
    }
}

void SoundManager::playMusic() {
    if(!Mix_PlayingMusic()){
        Mix_PlayMusic(music, -1);
    }
}

void SoundManager::pauseMusic() {
    if(!Mix_PausedMusic()) {
        Mix_PauseMusic();
    }
}

void SoundManager::resumeMusic() {
    if(Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}

void SoundManager::playClick() {
    Mix_PlayChannel( -1, click, 0 );
}

void SoundManager::playCrush() {
    Mix_PlayChannel( -1, crush, 0 );
}

void SoundManager::playGameOver() {
    Mix_PlayChannel( -1, gameOver, 0 );
}

void SoundManager::playLevelCompleted() {
    Mix_PlayChannel( -1, levelCompleted, 0 );
}

void SoundManager::setMute(bool onMute) {
    this->onMute = onMute;
}

bool SoundManager::isOnMute() {
    return this->onMute;
}

