#ifndef BLACKCOLOUR_H
#define BLACKCOLOUR_H

#include "Colour.h"

class BlackColour : public Colour
{
    public:
        BlackColour() : Colour(0, 0, 0) { }
        virtual ~BlackColour() {}
};

#endif // BLACKCOLOUR_H
