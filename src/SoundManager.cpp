#include "SoundManager.h"
#include <stdexcept>

#include <iostream>
using namespace std;

SoundManager* SoundManager::instance = NULL;
const std::string SoundManager::MUSIC_FILE_PATH = "resources/sound/music.ogg";

SoundManager::SoundManager() :
    music(NULL),
    onMute(false)
{
    loadMusic();
}

void SoundManager::close() {
    if(music != NULL)
        Mix_FreeMusic( music );
    Mix_HaltMusic();
}

void SoundManager::loadMusic() {
    music = Mix_LoadMUS(MUSIC_FILE_PATH.c_str());
    if(music == NULL) {
        throw std::runtime_error("!!! Error loading music file: " + MUSIC_FILE_PATH);
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

void SoundManager::setMute(bool onMute) {
    this->onMute = onMute;
}

bool SoundManager::isOnMute() {
    return this->onMute;
}

