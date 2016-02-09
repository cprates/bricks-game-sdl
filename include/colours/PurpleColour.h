#ifndef PURPLECOLOUR_H
#define PURPLECOLOUR_H

#include "Colour.h"

class PurpleColour : public Colour
{
    public:
        PurpleColour() : Colour(105, 9, 150) { }
        virtual ~PurpleColour() {}
};

#endif // PURPLECOLOUR_H
