#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "Engine.h"

using namespace std;

class Text : public Entity
{
    public:
        Text(const string text, SDL_Color color, int x, int y, short fontSize, Engine* engine, bool wild = false);
        virtual ~Text();
        virtual void onDraw(SDL_Renderer* renderer);
        void setAngle(const double angle);
        short getAngle();
        void setAlpha(short alpha);
        SDL_Texture* getTexture();

    private:
        SDL_Texture* texture;
        double angle;
};

#endif // TEXT_H
