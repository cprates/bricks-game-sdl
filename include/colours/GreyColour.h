#ifndef GREYCOLOUR_H
#define GREYCOLOUR_H

#include "Colour.h"

class GreyColour : public Colour
{
    public:
        GreyColour() :Colour(50, 50, 50) { }
        virtual ~GreyColour() {}
};

#endif // GREYCOLOUR_H
