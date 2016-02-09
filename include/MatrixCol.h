#ifndef MATRIXCOL_H
#define MATRIXCOL_H

#include <cstdlib>
#include <ctime>

#include "MatrixElement.h"
//
#include "Colour.h"
#include "RedColour.h"
#include "BlueColour.h"
#include "GreenColour.h"
#include "GreyColour.h"
#include "YellowColour.h"
#include "PurpleColour.h"


class MatrixCol
{
    public:
        static const Colour coloursSeed[];
        static const int coloursSeedSize;


        MatrixCol(int maxHeight);
        virtual ~MatrixCol();

        int getHeight();
        void addElement(MatrixElement* elem);
        MatrixElement* getElement(int row);
        void genRandomCol(int nColours);
        int reallocRows();
        void print();

    private:
        MatrixElement** col;
        int height, maxHeight;
};

#endif // MATRIXCOL_H
