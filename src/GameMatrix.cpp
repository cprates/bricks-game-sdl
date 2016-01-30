#include "GameMatrix.h"

/*
* x and y - matrix coords on sdl surface
*/
GameMatrix::GameMatrix(int x, int y, int maxWidth, int maxHeight) :
    width(0),
    _x(x),
    _y(y)
{
    this->maxWidth = maxWidth;
    this->maxHeight = maxHeight;
    this->matrix = new MatrixCol*[maxWidth];

    srand((unsigned)time(NULL));
}

GameMatrix::~GameMatrix() {
    for(int col = 0; col < width; col++) {
        delete matrix[col];
    }
    delete matrix;
}

bool GameMatrix::genColumn(int nColours) {
    if(width < maxWidth) {
        this->matrix[width] = new MatrixCol(maxHeight);
        this->matrix[width++]->genRandomCol(nColours);
        return true;
    }
    return false;
}

MatrixElement* GameMatrix::getElement(int col, int row) {
    return this->matrix[col]->getElement(row);
}

void GameMatrix::getAdjacentTwins(int sourfaceX, int sourfaceY, vector<MatrixElement*>* adjacentTwins) {
    //TODO: internamente traduz as coordenadas do click para o [x][y] do quadrado da matriz(a matriz precisa saber onde está a ser escrita e o tamanho de cada quadrado)
    //TODO: confirmar se os indices são validos. Invalidos é maiores que as colunas por exemplo. Rebenta com a aplicação
    int col = sourfaceX;
    int row = sourfaceY;
    Colour* c = this->matrix[col]->getElement(row)->getColour();
    return this->getAdjacentTwins(col, row, c, adjacentTwins);
}

// TODO: dont check origin
void GameMatrix::getAdjacentTwins(int col, int row, Colour *colour, vector<MatrixElement*>* adjacentTwins) {
    if(col >= this->width || col < 0) return;
    if(row >= this->matrix[col]->getHeight() || row < 0) return;

    MatrixElement *elem = this->matrix[col]->getElement(row);
    if(elem->getColour()->isEqual(colour) && !elem->toRemove) {
        adjacentTwins->push_back(elem);
        elem->toRemove = true;

        this->getAdjacentTwins(col, row+1, colour, adjacentTwins); // check above
        this->getAdjacentTwins(col, row-1, colour, adjacentTwins); // check below
        this->getAdjacentTwins(col+1, row, colour, adjacentTwins); // check left
        this->getAdjacentTwins(col-1, row, colour, adjacentTwins); // check right
    }
}

int GameMatrix::reallocElements() {
    int removedElements = 0;
    for(int col = 0; col < width; col++) {
        removedElements += this->matrix[col]->reallocRows();
    }
    removedElements += this->reallocColumns();

    return removedElements;
}

void GameMatrix::print()
{
    for(int col = 0; col < width; col++) {
        std::cout << "** col: " << col << " **" << std::endl;
        matrix[col]->print();
    }
}






/***********************************************
**              Private Methods               **
************************************************/

int GameMatrix::reallocColumns() {
    int cursor = 0;
    int removed = 0; // useful to calc score
    MatrixCol* column;

    for(int colIdx = 0; colIdx < width; colIdx++) {
        column = this->matrix[colIdx];
        if(column->getHeight() > 0 && cursor == colIdx) {
            cursor++;
            continue;
        }
        else if(column->getHeight() > 0 && cursor != colIdx) {
            this->matrix[cursor++] = this->matrix[colIdx];
        }
        else { // column->getHeight() == 0
            delete this->matrix[colIdx];
            removed++;
        }
    }
    this->width = cursor;

    return removed;
}
