#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SDL.h>

using namespace std;

class Entity
{
    public:
        //Entity(){}
        Entity(const int x, const int y, const int width, const int height, const bool wild = false);
        virtual ~Entity();
        void setID(const unsigned id);
        unsigned getID();
        virtual void onDraw(SDL_Renderer* renderer){}
        virtual void onUpdate(const unsigned elapsedTime){}
        bool isVisible();
        void setVisible(bool flag);
        bool isWild();
        void setWild(bool flag);
        SDL_Rect* getRect();
        void onClick(SDL_Event* ev);
        void onMouseOver(SDL_Event* ev);

    protected:
        bool visible;
        // An Entity is wild when only the Scene have a reference to it
        bool wild;
        SDL_Rect rect;

    private:
        unsigned id;
};

#endif // ENTITY_H
