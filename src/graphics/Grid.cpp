#include "Grid.h"

const std::string Grid::BLOCK_IMAGE_PATH = "block.png";

Grid::Grid(int x, int y, short width, short height, short blockWidth, short blockHeight, SDL_Renderer* renderer, bool wild) :
    Entity(x, y, width*blockWidth, height*blockHeight, renderer, wild),
    blockRect({0 ,0 ,blockWidth ,blockHeight})
{
    this->blockImage = new Sprite(BLOCK_IMAGE_PATH, 0, 0, blockRect.w, blockRect.h, renderer);
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

    //Make a target texture to render too
	gridImage = SDL_CreateTexture(this->entityRenderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, this->rect.w, this->rect.h);

	//Now render to the texture
	SDL_SetRenderTarget(this->entityRenderer, gridImage);
	SDL_RenderClear(this->entityRenderer);

    //TODO: Implement an lazy iterator for GameMatrix
    for(int col = 0; col < width; col++) {
        column = matrix[col];
        height = column->getHeight();
        for(int row = 0; row < height; row++) {
            cout << "X: " << dstRect.x << endl;
            cout << "Y: " << dstRect.y << endl;
            cout << "-------------" << endl;
            colour = column->getElement(row)->getColour();
            SDL_SetTextureColorMod( this->blockImage->getTexture(), colour->r, colour->g, colour->b );
            SDL_RenderCopy(this->entityRenderer, this->blockImage->getTexture(), NULL, &dstRect);
            dstRect.y -= this->blockRect.h;
        }
        dstRect.x += this->blockRect.w;
        dstRect.y = this->rect.h - this->blockRect.h;
    }

	//Detach the texture
	SDL_SetRenderTarget(this->entityRenderer, NULL);
}

void Grid::onDraw(SDL_Renderer* renderer) {
    if(gridImage == NULL) {
        return;
    }
	SDL_RenderCopyEx(renderer, this->gridImage, NULL, &this->rect, 0, NULL, SDL_FLIP_NONE);
}

void Grid::onUpdate(const unsigned elapsedTime) {

}
