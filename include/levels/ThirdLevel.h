#ifndef THIRDLEVEL_H
#define THIRDLEVEL_H

#include "Level.h"

class ThirdLevel : public Level
{
    public:
        ThirdLevel() {
            matrixCols = 9;
            nColours = 6;
            newColumnTime = 5;
            scoreToFinish = 135;
            levelID = 3;
            levelTitle = "Level 3";
        }
};

#endif // THIRDLEVEL_H
