#ifndef MATRIXELEMENT_H
#define MATRIXELEMENT_H

#include "colours/Colour.h"

class MatrixElement
{
    public:
        bool toRemove;

        MatrixElement(Colour* colour) : toRemove(false) {
            this->colour = colour;
        }
        virtual ~MatrixElement() {
            delete colour;
        }

        Colour* getColour() {return this->colour;}
    private:
        Colour *colour;
};

#endif // MATRIXELEMENT_H
