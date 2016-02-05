#ifndef MOVEXMODIFIER_H
#define MOVEXMODIFIER_H

#include "BaseModifier.h"

class MoveXModifier : public BaseModifier
{
    public:
        MoveXModifier(int from, int to, float duration) : BaseModifier(from, to, duration) {}

        void update(float value) {
            target->setPosX(value);
        }
};

#endif // MOVEXMODIFIER_H
