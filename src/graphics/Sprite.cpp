#include "Sprite.h"

Sprite::Sprite(const string imgPath, int x, int y, int width, int height, SDL_Renderer* renderer, bool wild) :
    Entity::Entity(x, y, width, height, renderer),
    texture(NULL),
    angle(0)
{
    this->wild = wild;
    this->create(imgPath, renderer);
}

Sprite::~Sprite() {
	if(texture != NULL) {
		SDL_DestroyTexture( texture );
	}
}

void Sprite::onDraw(SDL_Renderer* renderer) {
    if(texture == NULL) {
        return;
    }
	SDL_RenderCopyEx(renderer, this->texture, NULL, &this->rect, angle, NULL, SDL_FLIP_NONE);
}

bool Sprite::create(const string imgPath, SDL_Renderer* renderer) {
	SDL_Surface* imgSurface = IMG_Load(imgPath.c_str());
	if(imgSurface == NULL){
        cout << "!!! Can't load texture: " << imgPath << endl;
        cout << "!!! Error: " << IMG_GetError() << endl;
		return false;
	}
    SDL_SetColorKey( imgSurface, SDL_TRUE, SDL_MapRGB( imgSurface->format, 0x00, 0xFF, 0xFF ) );

    this->texture = SDL_CreateTextureFromSurface( renderer, imgSurface );
    if(this->texture == NULL){
        cout << "!!! Can't create texture: " << imgPath << endl;
        cout << "!!! Error: " << IMG_GetError() << endl;
        return false;
    }

    // Clean...
    SDL_FreeSurface( imgSurface );
	return true;
}

void Sprite::setAngle(const double angle) {
    this->angle = angle;
}

short Sprite::getAngle() {
    return this->angle;
}

void Sprite::setAlpha(short alpha) {
    if(this->texture != NULL){
        SDL_SetTextureAlphaMod(this->texture, alpha);
    }
}

SDL_Texture* Sprite::getTexture() {
    return this->texture;
}
