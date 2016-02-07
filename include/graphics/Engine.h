#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Scene.h"
#include "IOListener.h"

using namespace std;

class Engine
{
    public:
        static const string FONT_PATH;
        static const short  RENDERER_BG_COLOUR_RED   = 150;
        static const short  RENDERER_BG_COLOUR_GREEN = 150;
        static const short  RENDERER_BG_COLOUR_BLUE  = 150;
        static const short  RENDERER_BG_COLOUR_ALPHA = 255;

        Engine(const int windowWidth, const int windowHeight, const string windowTitle, const int fps = 30);
        virtual ~Engine();
        bool init();
        void start();
        void setScene(Scene* scene);
        void setSubScene(Scene* scene);
        SDL_Renderer* getRenderer();
        void setIOListener(IOListener* listener);
        SDL_Texture* renderText(const string text, short fontSize, SDL_Color colour);
        int getScreenWidth();
        int getScreenHeight();
        void detachSubScene();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Scene* scene;
        Scene* subScene; // useful for transitions between scenes
        IOListener* ioListener;
        bool shutdown;
        int wWidth, wHeight;
        string wTitle;
        int fpsRate;
        // 1 tick = 1 ms
        unsigned int ticksPerFrame;
        bool needDetachSubScene;

        void handleIO(SDL_Event* ev);
};

#endif // ENGINE_H
