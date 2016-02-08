#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>
#include <SDL_mixer.h>


class SoundManager
{
    public:
        static const std::string MUSIC_FILE_PATH;
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
        void setMute(bool onMute);
        bool isOnMute();


    private:
        static SoundManager* instance;
        Mix_Music* music;
        bool onMute;

        SoundManager();
        ~SoundManager();
        void loadMusic();

};

#endif // SOUNDMANAGER_H
