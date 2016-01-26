#ifndef BLUECOLOUR_H
#define BLUECOLOUR_H

#include "Colour.h"

class BlueColour : public Colour
{
    public:
        BlueColour() : Colour(0, 0, 200) { }
        virtual ~BlueColour() {}
};

#endif // BLUECOLOUR_H
