#include "ObjectV2.h"
#include "../engine/DataBus.h"
#include "../settings/controls.h"

namespace world {
    ObjectV2::ObjectV2(unsigned int newObjectId, ObjectState initialState) :
            objectId(newObjectId),
            state(initialState),
            controls(settings::objectInputSettings),
            sensitivity(settings::testWorld.mouseSensitivity)
    {
        updateDirection();
    }

    void ObjectV2::updateDirection() {
        frontVector.x = (float) (cos(glm::radians(-state.yaw)) * cos(glm::radians(state.pitch)));
        frontVector.y = (float) sin(glm::radians(state.pitch));
        frontVector.z = (float) (sin(glm::radians(-state.yaw)) * cos(glm::radians(state.pitch)));
        frontVector = glm::normalize(frontVector);
    }

    void ObjectV2::executeActions() {
        //move();
        rotate();
    }

    void ObjectV2::rotate() {
        if (xOffset == 0 && yOffset == 0) return;

        state.yaw += (float)xOffset;
        //state.pitch += (float)yOffset;

        if(state.pitch > 89.0f) state.pitch = 89.0f;
        if(state.pitch < -89.0f) state.pitch = -89.0f;

        xOffset = yOffset = 0;
        updateDirection();
    }

    void ObjectV2::move() {
        //behaviour->execute();
    }

    void ObjectV2::keyPressedAction(ActionList action) {
        if (onKeyPressedActionMethods.contains(action)) {
            return ((*this).*(onKeyPressedActionMethods[action]))();
        }
    }

    void ObjectV2::keyDownAction(ActionList action) {
        if (onKeyDownActionMethods.contains(action)) {
            ((*this).*(onKeyDownActionMethods[action]))();
        }
    }

    void ObjectV2::moveForwardMethod() {
        //behaviour->enqueueMoveForward();
    }

    void ObjectV2::moveBackwardMethod() {
        //behaviour->enqueueMoveBackward();
    }

    void ObjectV2::rotateLeftMethod() {
        //behaviour->enqueueRotateLeft();
    }

    void ObjectV2::rotateRightMethod() {
        //behaviour->enqueueRotateRight();
    }

    void ObjectV2::strafeLeftMethod() {
        //behaviour->enqueueStrafeLeft();
    }

    void ObjectV2::strafeRightMethod() {
        //behaviour->enqueueStrafeRight();
    }

    void ObjectV2::freeRotateMethod(double xPos, double yPos, double lastX, double lastY) {
        xOffset = xPos - lastX;
        yOffset = lastY - yPos;

        xOffset *= -sensitivity;
        yOffset *= sensitivity;
    }
} // world
