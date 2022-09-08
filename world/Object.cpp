//
// Created by dima on 27.08.22.
//

#include "Object.h"
#include "../settings/worldConfig.h"

namespace world {
    Object::Object(unsigned int newObjectId, ObjectState initialState) :
        objectId(newObjectId),
        state(initialState),
        controls(settings::objectInputSettings),
        sensitivity(settings::testWorld.mouseSensitivity)
    {
        updateDirection();
    }

    void Object::rotateObject(float objectSpeed) {
        state.yaw += objectSpeed;
        updateDirection();
    }

    void Object::updateDirection() {
        frontVector.x = (float) (cos(glm::radians(-state.yaw)) * cos(glm::radians(state.pitch)));
        frontVector.y = (float) sin(glm::radians(state.pitch));
        frontVector.z = (float) (sin(glm::radians(-state.yaw)) * cos(glm::radians(state.pitch)));
        frontVector = glm::normalize(frontVector);
    }

    void Object::moveObject(float objectSpeed) {
        state.position -= objectSpeed * frontVector;
    }

    void Object::strafeObject(float objectSpeed) {
        state.position += glm::normalize(glm::cross(frontVector, upVector)) * objectSpeed;
        updateDirection();
    }

    void Object::executeActions(float moveSpeed, float rotateSpeed) {
        if (getMovingState() != 0) {
            move(moveSpeed, rotateSpeed);
        }
        if (xOffset != 0 || yOffset != 0) {
            rotate();
        }
    }

    void Object::rotate() {
        state.yaw += (float)xOffset;
        //state.pitch += (float)yOffset;

        if(state.pitch > 89.0f) state.pitch = 89.0f;
        if(state.pitch < -89.0f) state.pitch = -89.0f;

        xOffset = yOffset = 0;
        updateDirection();
    }

    void Object::move(float moveSpeed, float rotateSpeed) {
        if (getMovingState() & SOULSLIKEGL_MOVE_FORWARD) moveObject(-moveSpeed);
        if (getMovingState() & SOULSLIKEGL_MOVE_BACKWARD) moveObject(moveSpeed);
        if (getMovingState() & SOULSLIKEGL_ROTATE_RIGHT) rotateObject(-rotateSpeed);
        if (getMovingState() & SOULSLIKEGL_ROTATE_LEFT) rotateObject(rotateSpeed);
        if (getMovingState() & SOULSLIKEGL_STRAFE_RIGHT) strafeObject(moveSpeed);
        if (getMovingState() & SOULSLIKEGL_STRAFE_LEFT) strafeObject(-moveSpeed);
        stopMoving(getMovingState());
    }

    void Object::keyPressedAction(ActionList action) {
        if (onKeyPressedActionMethods.contains(action)) {
            return ((*this).*(onKeyPressedActionMethods[action]))();
        }
    }

    void Object::keyDownAction(ActionList action) {
        if (onKeyDownActionMethods.contains(action)) {
            ((*this).*(onKeyDownActionMethods[action]))();
        }
    }

    void Object::moveForwardMethod() {
        movingState |= SOULSLIKEGL_MOVE_FORWARD;
    }

    void Object::moveBackwardMethod() {
        movingState |= SOULSLIKEGL_MOVE_BACKWARD;
    }

    void Object::rotateLeftMethod() {
        movingState |= SOULSLIKEGL_ROTATE_LEFT;
    }

    void Object::rotateRightMethod() {
        movingState |= SOULSLIKEGL_ROTATE_RIGHT;
    }

    void Object::strafeLeftMethod() {
        movingState |= SOULSLIKEGL_STRAFE_LEFT;
    }

    void Object::strafeRightMethod() {
        movingState |= SOULSLIKEGL_STRAFE_RIGHT;
    }

    void Object::freeRotateMethod(double xPos, double yPos, double lastX, double lastY) {
        xOffset = xPos - lastX;
        yOffset = lastY - yPos;

        xOffset *= -sensitivity;
        yOffset *= sensitivity;
    }

    unsigned int Object::getMovingState() const {
        return movingState;
    }

    void Object::stopMoving(unsigned int moving) {
        movingState ^= moving;
    }
} // world
