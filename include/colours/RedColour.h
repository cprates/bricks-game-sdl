#ifndef REDCOLOUR_H
#define REDCOLOUR_H

#include "Colour.h"

class RedColour : public Colour
{
    public:
        RedColour():Colour(200, 0, 0) { }
        virtual ~RedColour() {}
};

#endif // REDCOLOUR_H
