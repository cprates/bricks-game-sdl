#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <SDL.h>

class BaseModifier;

using namespace std;

class Entity
{
    public:
        //Entity(){}
        Entity(const int x, const int y, const int width, const int height, SDL_Renderer* renderer, const bool wild = false);
        virtual ~Entity();
        void setID(const unsigned id);
        unsigned getID();
        virtual void onDraw(SDL_Renderer* renderer){}
        virtual void onUpdate(const unsigned elapsedTime);
        virtual void setAlpha(short alpha) {};
        bool isVisible();
        void setVisible(bool flag);
        bool isWild();
        void setWild(bool flag);
        SDL_Rect* getRect();
        void setWidth(unsigned width);
        void setHeight(unsigned height);
        void setPosition(int x, int y);
        void setPosX(int x);
        void setPosY(int y);
        virtual void onClick(SDL_Event* ev);
        virtual void onMouseOver(SDL_Event* ev);
        void addModifier(BaseModifier* modifier);

    protected:
        bool visible;
        // An Entity is wild when only the Scene have a reference to it
        bool wild;
        SDL_Rect rect;
        SDL_Renderer* entityRenderer;
        vector<BaseModifier*> modifiersList;

    private:
        unsigned id;
};

#endif // ENTITY_H
