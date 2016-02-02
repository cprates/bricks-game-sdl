#include "Sprite.h"

Sprite::Sprite(int x, int y, int width, int height, bool wild) : Entity::Entity(x, y, width, height),
    texture(NULL),
    angle(0)
{
    this->wild = wild;
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

void Sprite::onUpdate(const unsigned elapsedTime) {

}

bool Sprite::create(const string imgPath, SDL_Renderer* renderer) {
	SDL_Surface* imgSurface = IMG_Load(imgPath.c_str());
	if(imgSurface == NULL){
		return false;
	}
    SDL_SetColorKey( imgSurface, SDL_TRUE, SDL_MapRGB( imgSurface->format, 0xFF, 0xFF, 0xFF ) );

    this->texture = SDL_CreateTextureFromSurface( renderer, imgSurface );
    if(this->texture == NULL){
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
