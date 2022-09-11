#ifndef SOULSLIKEGL_MOVE_H
#define SOULSLIKEGL_MOVE_H

#include "../Object.h"

namespace world::behaviours {

    class Move {
    public:
        explicit Move(Object *);

        void enqueueMoveForward(float numerator);
        void enqueueMoveBackward(float numerator);
        void enqueueStrafeLeft(float numerator);
        void enqueueStrafeRight(float numerator);
        void enqueueRotateLeft(float numerator);
        void enqueueRotateRight(float numerator);
        void execute();

    protected:
        Object *boundObject = nullptr;
        float moveQueue = 0.0f;
        float rotateQueue = 0.0f;
        float strafeQueue = 0.0f;
        float moveSpeed;
        float rotateSpeed;
        void enqueueMove(float numerator);
        void enqueueStrafe(float numerator);
        void enqueueRotate(float numerator);
        void executeMove();
        void executeStrafe();
        void executeRotate();
    };

} // behaviours

#endif //SOULSLIKEGL_MOVE_H
