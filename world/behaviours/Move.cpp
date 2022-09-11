#include "Move.h"
#include "../../render/gl/app.h"
#include "../../settings/worldConfig.h"

using namespace render;

namespace world::behaviours {

    Move::Move(Object *object) {
        boundObject = object;
        moveSpeed = settings::testWorld.objectSpeed;
        rotateSpeed = settings::testWorld.rotateSpeed;
    }

    void Move::execute() {
        executeMove();
        executeRotate();
        executeStrafe();
    }

    void Move::executeMove() {
        if (moveQueue == 0.0f) return;
        boundObject->state.position += moveQueue * boundObject->frontVector;
        moveQueue = 0.0f;
    }

    void Move::executeStrafe() {
        if (strafeQueue == 0.0f) return;
        boundObject->state.position -= glm::normalize(glm::cross(boundObject->frontVector, boundObject->upVector)) * strafeQueue;
        strafeQueue = 0.0f;
    }

    void Move::executeRotate() {
        if (rotateQueue == 0.0f) return;
        boundObject->state.yaw += rotateQueue;
        rotateQueue = 0.0f;
        // TODO: make it lazy
        boundObject->updateDirection();
    }

    void Move::enqueueMove(float numerator) {
        moveQueue += moveSpeed * numerator;
    }

    void Move::enqueueStrafe(float numerator) {
        strafeQueue += moveSpeed * numerator;
    }

    void Move::enqueueRotate(float numerator) {
        rotateQueue += rotateSpeed * numerator;
    }

    void Move::enqueueMoveForward(float numerator = App::deltaTime) {
        enqueueMove(numerator);
    }

    void Move::enqueueMoveBackward(float numerator = App::deltaTime) {
        enqueueMove(-numerator);
    }

    void Move::enqueueStrafeLeft(float numerator = App::deltaTime) {
        enqueueStrafe(-numerator);
    }

    void Move::enqueueStrafeRight(float numerator = App::deltaTime) {
        enqueueStrafe(numerator);
    }

    void Move::enqueueRotateLeft(float numerator = App::deltaTime) {
        enqueueRotate(-numerator);
    }

    void Move::enqueueRotateRight(float numerator = App::deltaTime) {
        enqueueRotate(numerator);
    }
} // behaviours
