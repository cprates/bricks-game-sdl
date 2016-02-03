#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"

using namespace std;

class Sprite : public Entity
{
    public:
        Sprite(const string imgPath, int x, int y, int width, int height, SDL_Renderer* renderer, bool wild = false);
        virtual ~Sprite();
        void onDraw(SDL_Renderer* renderer);
        void onUpdate(const unsigned elapsedTime);
        void setAngle(const double angle);
        short getAngle();
        void setAlpha(short alpha);
        SDL_Texture* getTexture();

    private:
        SDL_Texture* texture;
        double angle;

        bool create(const string imgPath, SDL_Renderer* renderer);
};

#endif // SPRITE_H
