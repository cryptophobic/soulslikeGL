#include "Object.h"
#include "../engine/DataBus.h"

namespace world {
    Object::Object(unsigned int newObjectId, ObjectState initialState) :
        objectId(newObjectId),
        state(initialState),
        controls(settings::objectInputSettings),
        sensitivity(settings::testWorld.mouseSensitivity),
        moveSpeed(settings::testWorld.objectSpeed),
        rotateSpeed(settings::testWorld.rotateSpeed),
        behaviour(new behaviours::Move(this))
    {
        updateDirection();
    }

    void Object::updateDirection() {
        frontVector.x = (float) (cos(glm::radians(-state.yaw)) * cos(glm::radians(state.pitch)));
        frontVector.y = (float) sin(glm::radians(state.pitch));
        frontVector.z = (float) (sin(glm::radians(-state.yaw)) * cos(glm::radians(state.pitch)));
        frontVector = glm::normalize(frontVector);
    }

    void Object::executeActions() {
        move();
        rotate();
    }

    void Object::rotate() {
        if (xOffset == 0 && yOffset == 0) return;

        state.yaw += (float)xOffset;
        //state.pitch += (float)yOffset;

        if(state.pitch > 89.0f) state.pitch = 89.0f;
        if(state.pitch < -89.0f) state.pitch = -89.0f;

        xOffset = yOffset = 0;
        updateDirection();
    }

    void Object::move() {
        behaviour->execute();
    }

    void Object::keyPressedAction(settings::ActionList action) {
        if (onKeyPressedActionMethods.contains(action)) {
            return ((*this).*(onKeyPressedActionMethods[action]))();
        }
    }

    void Object::keyDownAction(settings::ActionList action) {
        if (onKeyDownActionMethods.contains(action)) {
            ((*this).*(onKeyDownActionMethods[action]))();
        }
    }

    void Object::moveForwardMethod() {
        behaviour->enqueueMoveForward();
    }

    void Object::moveBackwardMethod() {
        behaviour->enqueueMoveBackward();
    }

    void Object::rotateLeftMethod() {
        behaviour->enqueueRotateLeft();
    }

    void Object::rotateRightMethod() {
        behaviour->enqueueRotateRight();
    }

    void Object::strafeLeftMethod() {
        behaviour->enqueueStrafeLeft();
    }

    void Object::strafeRightMethod() {
        behaviour->enqueueStrafeRight();
    }

    void Object::freeRotateMethod(double xPos, double yPos, double lastX, double lastY) {
        xOffset = xPos - lastX;
        yOffset = lastY - yPos;

        xOffset *= -sensitivity;
        yOffset *= sensitivity;
    }
} // world
