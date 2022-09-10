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
        state.pitch = objectToFollow->state.pitch - 40.0f;
        state.position = objectToFollow->state.position;
        updateDirection();
        glm::vec3 rightVector = glm::normalize(glm::cross(frontVector, upVector));
        state.position += glm::normalize(glm::cross(frontVector, rightVector)) * -6.0f; // up
        state.position += glm::normalize(glm::cross(upVector, rightVector)) * -7.0f; // back
    }

    void Camera::executeActions() {
        Object::executeActions();
        follow();
    }

    void Camera::bindToTheObject(Object *object) {
        objectToFollow = object;
        follow();
    }

} // world
