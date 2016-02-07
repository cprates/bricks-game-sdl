#ifndef MOVEXMODIFIER_H
#define MOVEXMODIFIER_H

#include "BaseModifier.h"

template<class T>
class MoveXModifier : public BaseModifier
{
    public:
        typedef void (T::* ClickCallback)();
        MoveXModifier(int from, int to, float duration) :
            BaseModifier(from, to, duration),
            callback(NULL),
            _thisForCallback(NULL)
        {}

        void update(float value) {
            target->setPosX(value);
        }

        void setCallback(ClickCallback callback, T* _this) {
            this->callback = callback;
            this->_thisForCallback = _this;
        }

        void onUpdate(const unsigned elapsedTime) {
            BaseModifier::onUpdate(elapsedTime);
            if(finished && callback != NULL)
                (_thisForCallback->*callback)();
        }

    private:
        ClickCallback callback;
        T* _thisForCallback;
};

#endif // MOVEXMODIFIER_H
