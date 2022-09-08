//
// Created by dima on 27.08.22.
//

#include "Camera.h"

#include "../settings/worldConfig.h"

namespace world {

    Camera::Camera(unsigned int newObjectId, ObjectState initialState) :
        Object(newObjectId, initialState),
        fov(settings::testWorld.cameraFow)
    {
        display = false;
        controls = settings::cameraInputSettings;
        onKeyDownActionMethods = {
                {ActionList::moveForward, &Camera::moveForwardMethod},
                {ActionList::moveBackward, &Camera::moveBackwardMethod},
                {ActionList::strafeLeft, &Camera::strafeLeftMethod},
                {ActionList::strafeRight, &Camera::strafeRightMethod},
        };
        updateDirection();
    }

    void Camera::follow() {
        if (objectToFollow == nullptr) return;
        state.yaw = objectToFollow->state.yaw;
        state.pitch = objectToFollow->state.pitch - 35.0f;
        state.position = objectToFollow->state.position;
        updateDirection();
        glm::vec3 rightVector = glm::normalize(glm::cross(frontVector, upVector));
        state.position += glm::normalize(glm::cross(frontVector, rightVector)) * -2.0f;
        moveObject(7.0f);
    }

    void Camera::executeActions(float moveSpeed, float rotateSpeed) {
        Object::executeActions(moveSpeed, rotateSpeed);
        follow();
    }

    void Camera::bindToTheObject(Object *object) {
        objectToFollow = object;
        follow();
    }

} // world
