#ifndef LEVEL_H
#define LEVEL_H


class Level
{
    public:
        short getMatrixCols() {return matrixCols;}
        short getNColours() {return nColours;}
        unsigned getNewColumnTime() {return newColumnTime;}
        unsigned getScoreToFinish() {return scoreToFinish;}

    protected:
        short matrixCols; // initial value
        short nColours;
        unsigned newColumnTime;
        unsigned scoreToFinish;

};

#endif // LEVEL_H
