#ifndef FIRSTLEVEL_H
#define FIRSTLEVEL_H

#include "Level.h"

class FirstLevel : public Level
{
    public:
        FirstLevel() {
            matrixCols = 6;
            nColours = 4;
            newColumnTime = 10;
            scoreToFinish = 50;
            levelID = 1;
            levelTitle = "Level 1";
        }
};

#endif // FIRSTLEVEL_H
