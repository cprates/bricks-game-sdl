#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H

#include <vector>
#include "MatrixElement.h"
#include "MatrixCol.h"
#include "Colour.h"

using namespace std;

class GameMatrix
{
    public:
        GameMatrix(int x, int y, int maxWidth, int maxHeight);
        virtual ~GameMatrix();

        bool genColumn(int nColours);
        MatrixElement* getElement(int col, int row);
        void getAdjacentTwins(int sourfaceX, int sourfaceY, vector<MatrixElement*>* adjacentTwins);
        void getAdjacentTwins(int x, int y, Colour *colour, vector<MatrixElement*>* adjacentTwins);
        int reallocElements();
        bool isThere(int col, int row);
        void print();
        MatrixCol** getMatrix();
        int getWidth();
        void clean();

    private:
        int width;
        int maxWidth, maxHeight;
        int _x, _y;
        MatrixCol** matrix;

        int reallocColumns();
};

#endif // GAMEMATRIX_H
