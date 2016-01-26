#include "MatrixCol.h"

const Colour MatrixCol::coloursSeed[] = {
    RedColour(),
    GreenColour(),
    BlueColour(),
    YellowColour(),
    GreyColour(),
    BlackColour()
    };
const int MatrixCol::coloursSeedSize = 6;


MatrixCol::MatrixCol(int maxHeight) :
    height(0)
{
    this->maxHeight = maxHeight;
    this->col = new MatrixElement*[maxHeight];
}

MatrixCol::~MatrixCol()
{
    for(int row = 0; row < height; row++) {
        delete this->col[row];
    }
    delete this->col;
}

int MatrixCol::getHeight() {
    return this->height;
}

void MatrixCol::addElement(MatrixElement* elem) {
    if(height < maxHeight) {
        this->col[height++] = elem;
    }
}

MatrixElement* MatrixCol::getElement(int row) {
    return this->col[row];
}

/*
* fills a column with random colors
*/
void MatrixCol::genRandomCol(int nColours) {
    int colourIdx = 0;
    int lastColour = (nColours > coloursSeedSize)? coloursSeedSize : nColours;

    for(int i = 0; i < this->maxHeight; i++) {
        colourIdx = (rand()%lastColour);
        this->addElement( new MatrixElement(new Colour(coloursSeed[colourIdx])) );
    }
}

int MatrixCol::reallocRows() {
    int cursor = 0;
    int removed = 0; // useful to calc score
    MatrixElement* elem;

    for(int row = 0; row < height; row++) {
        elem = this->col[row];
        if(!elem->toRemove && cursor == row) {
            cursor++;
            continue;
        }
        else if(!elem->toRemove && cursor != row) {
            this->col[cursor++] = this->col[row];
        }
        else { // elem->toRemove
            delete this->col[row];
            removed++;
        }
    }
    this->height = cursor;

    return removed;
}

void MatrixCol::print() {
    for(int row = 0; row < height; row++) {
        if(this->col[row]->toRemove) std::cout << "- ";
        this->col[row]->getColour()->print();
    }
}
