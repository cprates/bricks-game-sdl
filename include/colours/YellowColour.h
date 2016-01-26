#ifndef YELLOWCOLOUR_H
#define YELLOWCOLOUR_H

#include "Colour.h"

class YellowColour : public Colour
{
    public:
        YellowColour() : Colour(200, 200, 0) { }
        virtual ~YellowColour() {}
};

#endif // YELLOWCOLOUR_H
