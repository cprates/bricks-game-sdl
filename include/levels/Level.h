#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <string>

class Level
{
    public:
        short getMatrixCols() {return matrixCols;}
        short getNColours() {return nColours;}
        unsigned getNewColumnTime() {return newColumnTime;}
        int getScoreToFinish() {return scoreToFinish;}
        short getLevelID() {return levelID;}
        std::string getLevelTitle() {return levelTitle;}

    protected:
        short matrixCols; // initial value
        short nColours;
        unsigned newColumnTime;
        int scoreToFinish;
        short levelID;
        std::string levelTitle;

};

#endif // LEVEL_H
