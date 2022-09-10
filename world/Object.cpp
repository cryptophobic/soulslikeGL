#include "Object.h"
#include "../settings/worldConfig.h"
#include "../render/gl/app.h"

using namespace render;

namespace world {
    Object::Object(unsigned int newObjectId, ObjectState initialState) :
        objectId(newObjectId),
        state(initialState),
        controls(settings::objectInputSettings),
        sensitivity(settings::testWorld.mouseSensitivity),
        moveSpeed(settings::testWorld.objectSpeed),
        rotateSpeed(settings::testWorld.rotateSpeed)
    {
        updateDirection();
    }

    void Object::updateDirection() {
        frontVector.x = (float) (cos(glm::radians(-state.yaw)) * cos(glm::radians(state.pitch)));
        frontVector.y = (float) sin(glm::radians(state.pitch));
        frontVector.z = (float) (sin(glm::radians(-state.yaw)) * cos(glm::radians(state.pitch)));
        frontVector = glm::normalize(frontVector);
    }

    void Object::moveObject(int direction) {
        state.position += moveSpeed * App::deltaTime * (float) direction * frontVector;
    }

    void Object::rotateObject(int direction) {
        state.yaw += rotateSpeed * (float) direction * App::deltaTime;
        updateDirection();
    }

    void Object::strafeObject(int direction) {
        state.position -= glm::normalize(glm::cross(frontVector, upVector)) * moveSpeed * App::deltaTime * (float) direction;
        updateDirection();
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
        if (getMovingState() == 0) return;
        if (getMovingState() & SOULSLIKEGL_MOVE_FORWARD) moveObject(Directions::forward);
        if (getMovingState() & SOULSLIKEGL_MOVE_BACKWARD) moveObject(Directions::backward);
        if (getMovingState() & SOULSLIKEGL_ROTATE_RIGHT) rotateObject(Directions::right);
        if (getMovingState() & SOULSLIKEGL_ROTATE_LEFT) rotateObject(Directions::left);
        if (getMovingState() & SOULSLIKEGL_STRAFE_RIGHT) strafeObject(Directions::right);
        if (getMovingState() & SOULSLIKEGL_STRAFE_LEFT) strafeObject(Directions::left);
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
