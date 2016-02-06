#ifndef BUTTON_H
#define BUTTON_H

#include "Sprite.h"

template<class T, class R>
class Button: public Sprite
{
    public:
        typedef void (R::* ClickCallback)(Entity*, T*);
        Button(const string imgPath, int x, int y, int width, int height, T data, R* parent, SDL_Renderer* renderer, bool wild = false):
            Sprite(imgPath, x, y, width, height, renderer, wild),
            data(data),
            parent(parent),
            borderColor({255, 0, 0, 255}),
            drawBorder(false),
            scaleFactor(1.1)
        {
            //ctor
        }

        virtual ~Button() {};

        void setClickCallback(ClickCallback callback) {
            this->callback = callback;
        }

        virtual void onClick(SDL_Event* ev) {
            (parent->*callback)(this, &data);
        }

        virtual void onFocusChange(SDL_Event* ev, bool setFocus) {
            if(setFocus) {
                scaleSize(scaleFactor);
            }
            else {
                scaleSize(1);
            }
        }

    private:
        T data;
        R* parent;
        ClickCallback callback;
        SDL_Color borderColor;
        bool drawBorder;
        float scaleFactor;
};

#endif // BUTTON_H
