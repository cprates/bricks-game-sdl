#ifndef GRID_H
#define GRID_H

//#define __DEBUG

#include <SDL.h>
#include <string>

#include "Entity.h"
#include "GameMatrix.h"
#include "MatrixCol.h"
#include "Sprite.h"

class GameScene;

class Grid : public Entity
{
    public:
        typedef void (GameScene::* ClickCallback)(int, int);
        static const std::string BLOCK_IMAGE_PATH;
        void build(GameMatrix* matrix);

        Grid(int x, int y, short width, short height, short blockWidth, short blockHeight,
             GameScene* parent, SDL_Renderer* renderer, bool wild = false);
        virtual ~Grid();
        void onDraw(SDL_Renderer* renderer);
        void onClick(SDL_Event* ev);
        void onMouseOver(SDL_Event* ev);
        void setEventCallback( ClickCallback callback );
        ClickCallback clickCallback;


    private:
        SDL_Texture* gridImage;
        Sprite* blockImage;
        SDL_Rect blockRect;
        GameScene* parent;
        int matrixWidth;

        struct Coord{
            int x;
            int y;
        };
        Coord textureCoordsToMatrixIdx(int x, int y);
};

#endif // GRID_H
