#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <SDL.h>

#include "Entity.h"
#include "IOListener.h"

using namespace std;

class Scene : public IOListener
{
    public:
        static const unsigned MAX_CHILDS = 500;

        Scene(SDL_Renderer* renderer);
        virtual ~Scene();
        virtual void onDraw(SDL_Renderer* renderer);
        virtual void onUpdate(unsigned elapsedTime);
        bool attachChild(Entity* entity);
        bool detatchEntity(Entity* entity);
        // IOListener
        virtual void onMouseMove(SDL_Event* ev);
        virtual void onMouseButton(SDL_Event* ev);

    protected:
        SDL_Renderer* renderer;

    private:
        vector<Entity*> childs;
        unsigned entityIDSeed;
        Entity* lastClicked;
        Entity* lastOnFocus;

        Entity* searchTarget(const int x, const int y);
        bool overIt(const int x, const int y, SDL_Rect* rect);
        void notifyOnClick(Entity* target, SDL_Event* ev);

};

#endif // SCENE_H
