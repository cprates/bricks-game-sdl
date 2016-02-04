#ifndef BUTTON_H
#define BUTTON_H

#include "Sprite.h"

template<class T, class R>
class Button: public Sprite
{
    public:
        typedef void (R::* ClickCallback)(T*);
        Button(const string imgPath, int x, int y, int width, int height, T data, R* parent, SDL_Renderer* renderer, bool wild = false):
            Sprite(imgPath, x, y, width, height, renderer, wild),
            data(data),
            parent(parent)
        {
            //ctor
        }
        virtual ~Button() {};

        void setClickCallback(ClickCallback callback) {
            this->callback = callback;
        }

        virtual void onClick(SDL_Event* ev) {
            (parent->*callback)(&data);
        }

    private:
        T data;
        R* parent;
        ClickCallback callback;
};

#endif // BUTTON_H
