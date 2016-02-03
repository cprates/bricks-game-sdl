#ifndef FIRSTLEVEL_H
#define FIRSTLEVEL_H

#include "Level.h"

class FirstLevel : public Level
{
    public:
        FirstLevel() {
            matrixCols = 15;
            nColours = 3;
            newColumnTime = 15;
            scoreToFinish = 50;
        }
    private:
};

#endif // FIRSTLEVEL_H
