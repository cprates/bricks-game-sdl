#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>

class Colour
{
    public:
        int r, g, b;


        Colour(int r, int g, int b) { this->r = r; this->g = g; this->b = b;}
        Colour(Colour *c) { this->r = c->r; this->g = c->g; this->b = c->b;}

        bool isEqual(Colour *c) {
            if(c)
                return (r==c->r && g==c->g && b==c->b);
            else
                return false;
        }

        void print(){ std::cout << "RGB(" << r << ", " << g << ", " << b << ")" << std::endl; }
};

#endif // COLOUR_H
