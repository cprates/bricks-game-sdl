#ifndef LEVEL_H
#define LEVEL_H


class Level
{
    public:
        short getMatrixCols() {return matrixCols;}
        short getNColours() {return nColours;}
        unsigned getNewColumnTime() {return newColumnTime;}
        int getScoreToFinish() {return scoreToFinish;}
        short getLevelID() {return levelID;}

    protected:
        short matrixCols; // initial value
        short nColours;
        unsigned newColumnTime;
        int scoreToFinish;
        short levelID;

};

#endif // LEVEL_H
