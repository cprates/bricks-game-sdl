#ifndef IOLISTENER_H
#define IOLISTENER_H

#include <SDL.h>

class IOListener
{
    public:
        virtual void onMouseMove(SDL_Event* ev) = 0;
        virtual void onMouseButton(SDL_Event* ev) = 0;
};

#endif // IOLISTENER_H
