#ifndef SOULSLIKEGL_MOVE_H
#define SOULSLIKEGL_MOVE_H

#include "../Object.h"
#include "../../engine/DataBus.h"
#include "Ability.h"

namespace world::abilities {

    class Move : public Ability {
    public:
        explicit Move(Object *);

        void enqueueMoveForward(float numerator = DataBus::deltaTime);
        void enqueueMoveBackward();
        void enqueueStrafeLeft(float numerator = DataBus::deltaTime);
        void enqueueStrafeRight(float numerator = DataBus::deltaTime);
        void enqueueRotateLeft(float numerator = DataBus::deltaTime);
        void enqueueRotateRight(float numerator = DataBus::deltaTime);
        void execute() override;

    protected:
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

} // abilities

#endif //SOULSLIKEGL_MOVE_H
