//
// Created by dima on 27.08.22.
//

#include "Camera.h"

#include "../settings/worldConfig.h"

namespace world {
    // TODO: Code smells bad
    Camera::Camera(CameraStateStruct initialState) : state(initialState) {
        display = false;
        controls = settings::cameraInputSettings;
        onKeyPressedActionMethods = {
                {ActionList::moveForward, &Camera::moveForwardMethod},
                {ActionList::moveBackward, &Camera::moveBackwardMethod},
                {ActionList::strafeLeft, &Camera::strafeLeftMethod},
                {ActionList::strafeRight, &Camera::strafeRightMethod},
        };
    }

    void Camera::follow() {
        state.yaw = objectToFollow->state.yaw;
        state.pitch = -35.0f;
        state.position = objectToFollow->state.position;
        updateDirection();
        moveObject(7.0f);

        glm::vec3 rightVector = glm::normalize(glm::cross(frontVector, upVector));

        // TODO: what's going on there
        state.position += glm::normalize(glm::cross(frontVector, rightVector)) * -2.0f;
    }

    void Camera::bindObjectToFollow(Object *object) {
        objectToFollow = object;
        follow();
    }

} // world
