#ifndef SOULSLIKEGL_MOVE_H
#define SOULSLIKEGL_MOVE_H

namespace world {
    class Object;
}

#include "../Object.h"
#include "../../engine/DataBus.h"

namespace world::behaviours {

    class Move {
    public:
        explicit Move(Object *);

        void enqueueMoveForward(float numerator = DataBus::deltaTime);
        void enqueueMoveBackward(float numerator = DataBus::deltaTime);
        void enqueueStrafeLeft(float numerator = DataBus::deltaTime);
        void enqueueStrafeRight(float numerator = DataBus::deltaTime);
        void enqueueRotateLeft(float numerator = DataBus::deltaTime);
        void enqueueRotateRight(float numerator = DataBus::deltaTime);
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
