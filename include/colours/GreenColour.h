#ifndef GREENCOLOUR_H
#define GREENCOLOUR_H

#include "Colour.h"

class GreenColour : public Colour
{
    public:
        GreenColour() : Colour(0, 200, 0) { }
        virtual ~GreenColour() {}
};

#endif // GREENCOLOUR_H
