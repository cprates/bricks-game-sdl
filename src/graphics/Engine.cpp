#include "Engine.h"
#include <chrono>

Engine::Engine(const int windowWidth, const int windowHeight, const string windowTitle, const int fps) :
    window(NULL),
    renderer(NULL),
    scene(NULL),
    ioListener(NULL),
    shutdown(false),
    wWidth(windowWidth),
    wHeight(windowHeight),
    wTitle(windowTitle),
    fpsRate(fps),
    ticksPerFrame(1000 / fpsRate)
{
}

Engine::~Engine()
{
	SDL_DestroyRenderer( renderer );
	renderer = NULL;
	SDL_DestroyWindow( window );
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}



bool Engine::init()
{
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
		cout << "!!! SDL initialization Error." << endl;
		cout << "!!! SDL Error: " << endl << SDL_GetError() << endl;
		return false;
	}
	else {
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			cout << "--- Linear texture filtering not enabled!" << endl;
		}

		window = SDL_CreateWindow( wTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wWidth, wHeight, SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			cout << "!!! Window could not be created!" << endl;
			cout << "!!! SDL Error: " << endl <<  SDL_GetError() << endl;
			return false;
		}
		else {
			//renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE );
			if( renderer == NULL ) {
				cout << "!!! Cant create the Renderer!" << endl;
				cout << "!!! SDL Error: " << endl << SDL_GetError() << endl;
			}
			else {
                SDL_SetRenderDrawColor( this->renderer, RENDERER_BG_COLOUR_RED, RENDERER_BG_COLOUR_GREEN,
                       RENDERER_BG_COLOUR_BLUE, RENDERER_BG_COLOUR_ALPHA );
				//Initialize PNG system
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					cout << "!!! Error initializing SDL_image!" << endl;
					cout << "!!! SDL_image Error: " << endl << IMG_GetError() << endl;
					return false;
				}
			}
		}
	}

	return true;
}

void Engine::start() {
    unsigned ticksCounter = SDL_GetTicks();
    unsigned elapsedTicks = 0;
    unsigned elapsedTime = SDL_GetTicks();
    SDL_Event e;

    while(!shutdown) {
        this->handleIO(&e);

        SDL_RenderClear( this->renderer );
        // Update and Draw Scene
        if(this->scene != NULL) {
            this->scene->onUpdate(SDL_GetTicks() - elapsedTime);
            elapsedTime = SDL_GetTicks();
            this->scene->onDraw(this->renderer);
        }
        SDL_RenderPresent( this->renderer );

        // Limit FPS Rate
        elapsedTicks = SDL_GetTicks() - ticksCounter;
        if( elapsedTicks < ticksPerFrame ) {
            SDL_Delay( ticksPerFrame - elapsedTicks );
        }
        ticksCounter = SDL_GetTicks();
    }
}

/**
* Set the scene to be rendered by the engine
**/
void Engine::setScene(Scene* scene) {
    this->scene = scene;
}

SDL_Renderer* Engine::getRenderer() {
    return this->renderer;
}

void Engine::setIOListener(IOListener* listener) {
    this->ioListener = listener;
}

void Engine::handleIO(SDL_Event* ev) {
    while( SDL_PollEvent(ev) != 0 ) {
        switch(ev->type) {
            case SDL_QUIT:
                shutdown = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                if(this->ioListener != NULL) {
                    this->ioListener->onMouseButton(ev);
                }
                break;
            case SDL_MOUSEMOTION:
                if(this->ioListener != NULL) {
                    this->ioListener->onMouseMove(ev);
                }
                break;
        }
    }
}
