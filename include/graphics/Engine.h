#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Scene.h"
#include "IOListener.h"

using namespace std;

class Engine
{
    public:
        static const short  RENDERER_BG_COLOUR_RED   = 0;
        static const short  RENDERER_BG_COLOUR_GREEN = 0;
        static const short  RENDERER_BG_COLOUR_BLUE  = 0;
        static const short  RENDERER_BG_COLOUR_ALPHA = 255;

        Engine(const int windowWidth, const int windowHeight, const string windowTitle, const int fps = 30);
        virtual ~Engine();
        bool init();
        void start();
        void setScene(Scene* scene);
        SDL_Renderer* getRenderer();
        void setIOListener(IOListener* listener);

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Scene* scene;
        IOListener* ioListener;
        bool shutdown;
        int wWidth, wHeight;
        string wTitle;
        int fpsRate;
        // 1 tick = 1 ms
        unsigned int ticksPerFrame;

        void handleIO(SDL_Event* ev);

};

#endif // ENGINE_H
