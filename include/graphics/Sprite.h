#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"

using namespace std;

class Sprite : public Entity
{
    public:
        Sprite(int x, int y, int width, int height, bool wild = false);
        virtual ~Sprite();
        bool create(const string imgPath, SDL_Renderer* renderer);
        void onDraw(SDL_Renderer* renderer);
        void onUpdate(const unsigned elapsedTime);
        void setAngle(const double angle);
        short getAngle();
        void setAlpha(short alpha);

    private:
        SDL_Texture* texture;
        double angle;
};

#endif // SPRITE_H
