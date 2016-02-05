#include "Text.h"

Text::Text(const string text, SDL_Color colour, int x, int y, short fontSize, Engine* engine, bool wild) :
    Entity::Entity(x, y, 0, 0, engine->getRenderer()),
    texture(NULL),
    angle(0)
{
    this->wild = wild;
    texture = engine->renderText(text, fontSize, colour);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

Text::~Text() {
	if(texture != NULL) {
		SDL_DestroyTexture(texture);
	}
}

void Text::onDraw(SDL_Renderer* renderer) {
    if(texture == NULL) {
        return;
    }
	SDL_RenderCopyEx(renderer, this->texture, NULL, &this->rect, angle, NULL, SDL_FLIP_NONE);
}

void Text::setAngle(const double angle) {
    this->angle = angle;
}

short Text::getAngle() {
    return this->angle;
}

void Text::setAlpha(short alpha) {
    if(this->texture != NULL){
        SDL_SetTextureAlphaMod(this->texture, alpha);
    }
}

SDL_Texture* Text::getTexture() {
    return this->texture;
}
