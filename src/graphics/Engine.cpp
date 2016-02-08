#include "Engine.h"
#include "SoundManager.h"
#include <chrono>

const string Engine::FONT_PATH = "font/font.ttf";

Engine::Engine(const int windowWidth, const int windowHeight, const string windowTitle, const int fps) :
    window(NULL),
    renderer(NULL),
    scene(NULL),
    subScene(NULL),
    ioListener(NULL),
    shutdown(false),
    wWidth(windowWidth),
    wHeight(windowHeight),
    wTitle(windowTitle),
    fpsRate(fps),
    ticksPerFrame(1000 / fpsRate),
    needDetachSubScene(false)
{
}

Engine::~Engine()
{
	SDL_DestroyRenderer( renderer );
	renderer = NULL;
	SDL_DestroyWindow( window );
	window = NULL;

    SoundManager::getInstance()->close();

    Mix_Quit();
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}



bool Engine::init()
{
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 ) {
		cout << "!!! SDL initialization Error." << endl;
		cout << "!!! SDL Error: " << endl << SDL_GetError() << endl;
		return false;
	}

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
        cout << "--- Linear texture filtering not enabled!" << endl;
    }

    window = SDL_CreateWindow( wTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wWidth, wHeight, SDL_WINDOW_SHOWN );
    if( window == NULL ) {
        cout << "!!! Window could not be created!" << endl;
        cout << "!!! SDL Error: " << endl <<  SDL_GetError() << endl;
        return false;
    }

    //renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE );
    if( renderer == NULL ) {
        cout << "!!! Cant create the Renderer!" << endl;
        cout << "!!! SDL Error: " << endl << SDL_GetError() << endl;
        return false;
    }

    SDL_SetRenderDrawColor( this->renderer, RENDERER_BG_COLOUR_RED, RENDERER_BG_COLOUR_GREEN,
           RENDERER_BG_COLOUR_BLUE, RENDERER_BG_COLOUR_ALPHA );
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // SDL_img
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        cout << "!!! Error initializing SDL_image!" << endl;
        cout << "!!! SDL_image Error: " << endl << IMG_GetError() << endl;
        return false;
    }

    // SDL_ttf
    if( TTF_Init() != 0 ) {
        cout << "!!! Error initializing SDL_ttf!" << endl;
        cout << "!!! SDL_ttf Error: " << endl << TTF_GetError() << endl;
        return false;
    }

    // SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        cout << "!!! Error initializing SDL_mixer!" << endl;
        cout << "!!! SDL_mixer Error: " << endl << Mix_GetError() << endl;
    }

	return true;
}

void Engine::start() {
    unsigned ticksCounter = SDL_GetTicks();
    unsigned elapsedTicks = 0;
    unsigned elapsedTime = SDL_GetTicks();
    SDL_Event e;

    while(!shutdown) {
        if(needDetachSubScene) {
            subScene = NULL;
            needDetachSubScene = false;
        }
        this->handleIO(&e);

        SDL_RenderClear( this->renderer );
        // Update and Draw Scene
        if(this->scene != NULL) {
            this->scene->onUpdate(SDL_GetTicks() - elapsedTime);
            this->scene->onDraw(this->renderer);
        }
        if(this->subScene != NULL) {
            this->subScene->onUpdate(SDL_GetTicks() - elapsedTime);
            this->subScene->onDraw(this->renderer);
        }
        elapsedTime = SDL_GetTicks();
        SDL_RenderPresent(this->renderer);

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

void Engine::setSubScene(Scene* scene) {
    this->subScene = scene;
}

SDL_Renderer* Engine::getRenderer() {
    return this->renderer;
}

void Engine::setIOListener(IOListener* listener) {
    this->ioListener = listener;
}

int Engine::getScreenWidth() {
    return this->wWidth;
}

int Engine::getScreenHeight() {
    return this->wHeight;
}

void Engine::detachSubScene() {
    needDetachSubScene = true;
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

SDL_Texture* Engine::renderText(const string text, short fontSize, SDL_Color colour) {
	TTF_Font* font = TTF_OpenFont(FONT_PATH.c_str(), fontSize);
	if(font == NULL) {
        cout << "!!! Error while loagind font!" << endl;
        cout << "!!! SDL_ttf Error: " << endl << TTF_GetError() << endl;
        return NULL;
	}

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), colour);
    if(textSurface == NULL) {
        cout << "!!! Unable to render text!" << endl;
        cout << "!!! SDL_ttf Error: " << endl << TTF_GetError() << endl;
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(texture == NULL) {
        cout << "!!! Unable to create texture from rendered text!" << endl;
        cout << "!!! SDL_ttf Error: " << endl << TTF_GetError() << endl;
        return NULL;
    }

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return texture;
}

