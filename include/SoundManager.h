#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>
#include <SDL_mixer.h>


class SoundManager
{
    public:
        static const std::string MUSIC_FILE_PATH;
        static const std::string CLICK_FILE_PATH;
        static const std::string CRUSH_FILE_PATH;
        static const std::string GAMEOVER_FILE_PATH;
        static const std::string LEVEL_COMPLETED_FILE_PATH;

        static SoundManager* getInstance() {
            if(instance == NULL) {
                instance = new SoundManager();
            }

            return instance;
        }

        void close();
        void playMusic();
        void pauseMusic();
        void resumeMusic();
        void playClick();
        void playCrush();
        void playGameOver();
        void playLevelCompleted();
        void setMute(bool onMute);
        bool isOnMute();


    private:
        static SoundManager* instance;
        Mix_Music* music;
        Mix_Chunk* click;
        Mix_Chunk* crush;
        Mix_Chunk* gameOver;
        Mix_Chunk* levelCompleted;
        bool onMute;

        SoundManager();
        ~SoundManager();
        void loadMusic();

};

#endif // SOUNDMANAGER_H
