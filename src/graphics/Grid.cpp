#include "Grid.h"
#include <cmath>

const std::string Grid::BLOCK_IMAGE_PATH = "resources/block.png";

Grid::Grid(int x, int y, short width, short height, short blockWidth, short blockHeight, GameScene* parent, SDL_Renderer* renderer, bool wild) :
    Entity(x, y, width*blockWidth, height*blockHeight, renderer, wild),
    gridImage(NULL),
    blockRect({0 ,0 ,blockWidth ,blockHeight}),
    parent(parent),
    matrixWidth(0),
    drawBlockBorder(false)
{
    blockImage = new Sprite(BLOCK_IMAGE_PATH, 0, 0, blockRect.w, blockRect.h, renderer);
    blockBorder.w = blockWidth;
    blockBorder.h = blockHeight;
}

Grid::~Grid()
{
	if(this->gridImage != NULL) {
		SDL_DestroyTexture( this->gridImage );
	}
    delete this->blockImage;
}

void Grid::build(GameMatrix* gm) {
    MatrixCol** matrix = gm->getMatrix();
    int width = gm->getWidth();
    MatrixCol* column;
    int height = 0;
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = this->rect.h - this->blockRect.h;
    dstRect.w = this->blockRect.w;
    dstRect.h = this->blockRect.h;
    Colour* colour;

    if(gridImage == NULL) {
        gridImage = SDL_CreateTexture(this->entityRenderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, this->rect.w, this->rect.h);
    }
    SDL_SetRenderDrawColor(this->entityRenderer, 255, 255, 255, 20);
    SDL_SetTextureBlendMode(gridImage, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(this->entityRenderer, gridImage);
	SDL_RenderClear(this->entityRenderer);

    //TODO: Implement a lazy iterator for GameMatrix to clean this mess
    for(int col = width-1; col >= 0; col--) { // invert the matrix
        column = matrix[col];
        height = column->getHeight();
        for(int row = 0; row < height; row++) {
            colour = column->getElement(row)->getColour();
            SDL_SetTextureColorMod( this->blockImage->getTexture(), colour->r, colour->g, colour->b );
            SDL_RenderCopy(this->entityRenderer, this->blockImage->getTexture(), NULL, &dstRect);
            dstRect.y -= this->blockRect.h;
        }
        dstRect.x += this->blockRect.w;
        dstRect.y = this->rect.h - this->blockRect.h;
    }
	SDL_SetRenderTarget(this->entityRenderer, NULL);

	this->matrixWidth = gm->getWidth();
}

void Grid::setEventCallback( ClickCallback callback ) {
   this->clickCallback = callback;
}

void Grid::onDraw(SDL_Renderer* renderer) {
    if(gridImage == NULL) {
        return;
    }
	SDL_RenderCopyEx(renderer, this->gridImage, NULL, &this->rect, 0, NULL, SDL_FLIP_NONE);

	if(drawBlockBorder) {
        SDL_SetRenderDrawColor( renderer, BBORDER_RED, BBORDER_GREEN, BBORDER_BLUE, BBORDER_ALPHA );
        SDL_RenderDrawRect( renderer, &blockBorder );
	}

#ifdef __DEBUG
    SDL_Rect outlineRect = { rect.x, rect.y, rect.w, rect.h};
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderDrawRect( renderer, &outlineRect );
    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
#endif
}

void Grid::onClick(SDL_Event* ev) {
    if(this->clickCallback != NULL) {
        Coord idx = textureCoordsToMatrixIdx(ev->button.x, ev->button.y);
        // notify GameScene
        (*parent.*clickCallback)(idx.x, idx.y);
    }
}

void Grid::onMouseOver(SDL_Event* ev) {
    int col = (ev->button.x - this->rect.x) / this->blockRect.w;
    int row = (ev->button.y - this->rect.y) / this->blockRect.h;

    blockBorder.x = col * blockRect.w + rect.x;
    blockBorder.y = row * blockRect.h + rect.y;
}

void Grid::onFocusChange(SDL_Event* ev, bool getFocus) {
    drawBlockBorder = getFocus;
}

Grid::Coord Grid::textureCoordsToMatrixIdx(int x, int y) {
    Coord idx;
    int nRows = this->rect.h / this->blockRect.h - 1;
    int col = (this->matrixWidth - ((x - this->rect.x) / this->blockRect.w)) - 1;
    int row = nRows - ((y - this->rect.y) / this->blockRect.h);
    idx.x = col;
    idx.y = row;

    return idx;
}


void Grid::setAlpha(short alpha) {
    if(this->gridImage != NULL){
        SDL_SetTextureAlphaMod(this->gridImage, alpha);
    }
}
