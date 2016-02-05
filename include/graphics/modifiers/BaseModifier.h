#ifndef BASEMODIFIER_H
#define BASEMODIFIER_H

#include "Entity.h"

class BaseModifier
{
    public:
        BaseModifier(int from, int to, float duration) {
            this->target= NULL;
            this->span = (to - from);
            this->fromValue = from;
            this->duration = duration;
            this->finished = false;
            this->elapsedTime = 0.0;
        }

        virtual ~BaseModifier() {}

        virtual void update(float value) {}

        void setTarget(Entity* target) {
            this->target = target;
        }

        void onUpdate(const unsigned elapsedTime) {
            if(target == NULL || finished) return;

            float elapsedTimeMS = elapsedTime /1000.0;

			float secondsElapsedUsed;
			if(this->elapsedTime + elapsedTimeMS < duration) {
				secondsElapsedUsed = elapsedTimeMS;
			}
			else {
				secondsElapsedUsed = duration - this->elapsedTime;
			}

			this->elapsedTime += secondsElapsedUsed;
            float percentageDone = this->elapsedTime / duration;
            update(fromValue + percentageDone * span);

			if(duration != -1 && this->elapsedTime >= duration) {
				this->elapsedTime = duration;
				finished = true;
			}
        }

        bool isFinished() { return finished; }

    private:
        float duration, span, fromValue;
        float elapsedTime;
        bool finished;

    protected:
        Entity* target;
};

#endif // BASEMODIFIER_H
