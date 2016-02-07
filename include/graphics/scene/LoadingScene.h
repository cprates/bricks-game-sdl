#ifndef LOADINGSCENE_H
#define LOADINGSCENE_H

#include "Sprite.h"
#include "Engine.h"
#include "Level.h"

class LoadingScene : public Scene
{
    public:
        static const string FROMLEFT_FILE_PATH;
        static const string FROMRIGHT_FILE_PATH;
        static const float DURATION;
        static const float HIDE_TIME;
        static const float DONE_TIME;
        LoadingScene(Engine* engine, SDL_Renderer* renderer);
        virtual ~LoadingScene();
        virtual void onUpdate(unsigned elapsedTime);
        void show();

    private:
        Sprite* fromLeftSprite;
        Sprite* fromRightSprite;
        short step;
        unsigned counter;

        void hide();
        void done();
};

#endif // LOADINGSCENE_H
