#ifndef SECONDTLEVEL_H
#define SECONDTLEVEL_H

#include "Level.h"

class SecondLevel : public Level
{
    public:
        SecondLevel() {
            matrixCols = 8;
            nColours = 5;
            newColumnTime = 6;
            scoreToFinish = 120;
            levelID = 2;
        }
    private:
};

#endif // SECONDTLEVEL_H
