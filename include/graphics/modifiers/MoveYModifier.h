#ifndef MOVEYMODIFIER_H
#define MOVEYMODIFIER_H

#include "BaseModifier.h"

class MoveYModifier : public BaseModifier
{
    public:
        MoveYModifier(int from, int to, float duration) : BaseModifier(from, to, duration) {}

        void update(float value) {
            target->setPosY(value);
        }
};

#endif // MOVEYMODIFIER_H
