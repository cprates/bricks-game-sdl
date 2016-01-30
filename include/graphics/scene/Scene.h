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
        Scene();
        virtual ~Scene();
        virtual void onDraw(SDL_Renderer* renderer);
        virtual void onUpdate(const unsigned elapsedTime);
        void onMouseEvent(SDL_Event* ev);
        bool attachChild(Entity* entity);
        bool detatchEntity(Entity* entity);

    private:
        vector<Entity*> childs;
        int entityIDSeed;

};

#endif // SCENE_H
