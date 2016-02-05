#ifndef ALPHAMODIFIER_H
#define ALPHAMODIFIER_H

#include "BaseModifier.h"

class AlphaModifier : public BaseModifier
{
    public:
        AlphaModifier(int from, int to, float duration) : BaseModifier(from, to, duration) {}

        void update(float value) {
            target->setAlpha(value);
        }

};

#endif // ALPHAMODIFIER_H
