//
// Created by dima on 27.08.22.
//

#include "Object.h"
#include "../settings/worldConfig.h"

namespace world {
    // TODO: Code smells
    Object::Object() {
        frontVector.x = (float) cos((glm::radians(-yaw)) * cos(glm::radians(pitch)));
        frontVector.y = (float) sin(glm::radians(pitch));
        frontVector.z = (float) (sin(glm::radians(-yaw)) * cos(glm::radians(pitch)));
        frontVector = glm::normalize(frontVector);

        controls = settings::objectInputSettings;
    }

    void Object::rotateObject(float objectSpeed) {
        yaw += objectSpeed;
        updateDirection();
    }

    void Object::updateDirection() {
        frontVector.x = (float) cos((glm::radians(-yaw)) * cos(glm::radians(pitch)));
        frontVector.y = (float) sin(glm::radians(pitch));
        frontVector.z = (float) (sin(glm::radians(-yaw)) * cos(glm::radians(pitch)));
        frontVector = glm::normalize(frontVector);
    }

    void Object::moveObject(float objectSpeed) {
        position -= objectSpeed * frontVector;
    }

    void Object::strafeObject(float objectSpeed) {
        position += glm::normalize(glm::cross(frontVector, upVector)) * objectSpeed;
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

    void Object::onKeyDownAction(ActionList action) {
        if (onKeyDownActionMethods.contains(action)) {
            ((*this).*(onKeyDownActionMethods[action]))();
        }
    }

    void Object::onKeyPressedAction(ActionList action) {
        if (onKeyPressedActionMethods.contains(action)) {
            ((*this).*(onKeyPressedActionMethods[action]))();
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

    unsigned int Object::getMovingState() const {
        return movingState;
    }

    void Object::stopMoving(unsigned int moving) {
        movingState ^= moving;
    }
} // world
