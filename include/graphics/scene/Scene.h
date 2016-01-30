#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <SDL.h>

#include "Entity.h"

using namespace std;

class Scene
{
    public:
        static const unsigned MAX_CHILDS = 500;

        Scene();
        virtual ~Scene();
        virtual void onDraw(SDL_Renderer* renderer);
        virtual void onUpdate(unsigned elapsedTime);
        void onMouseEvent(SDL_Event* ev); ///////////////////////////////////////////////
        bool attachChild(Entity* entity);
        bool detatchEntity(Entity* entity);

    private:
        vector<Entity*> childs;
        unsigned entityIDSeed;

};

#endif // SCENE_H
