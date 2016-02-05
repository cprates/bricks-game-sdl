#ifndef RULER_H
#define RULER_H

#include "Level.h"

class Ruler
{
    public:
        Ruler() {
            score = 0;
        }

        bool levelCompleted(Level* level) {
            return score >= level->getScoreToFinish();
        }

        int getScore() {
            return score;
        }

        void incrementScore(int score) {
            this->score += score;
        }

        void reset() {
            score = 0;
        }

    private:
        int score;
};

#endif // RULER_H
