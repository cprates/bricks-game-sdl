#ifndef GRID_H
#define GRID_H

#include <SDL.h>
#include <string>

#include "Entity.h"
#include "GameMatrix.h"
#include "MatrixCol.h"
#include "Sprite.h"

class Grid : public Entity
{
    public:
        static const std::string BLOCK_IMAGE_PATH;
        void build(GameMatrix* matrix);

        Grid(int x, int y, short width, short height, short blockWidth, short blockHeight, SDL_Renderer* renderer, bool wild = false);
        virtual ~Grid();
        void onUpdate(const unsigned elapsedTime);
        void onDraw(SDL_Renderer* renderer);


    private:
        SDL_Texture* gridImage;
        Sprite* blockImage;
        SDL_Rect blockRect;
};

#endif // GRID_H
