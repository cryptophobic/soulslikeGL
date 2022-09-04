//
// Created by dima on 27.08.22.
//

#include "Camera.h"

#include <utility>
#include "../settings/worldConfig.h"

namespace world {
    // TODO: Code smells
    Camera::Camera() : sensitivity(settings::testWorld.cameraSettings.sensitivity) {
        auto cameraSettings = settings::testWorld.cameraSettings;
        yaw = cameraSettings.yaw;
        pitch = cameraSettings.pitch;
        fov = cameraSettings.fov;
        position = cameraSettings.position;
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
        frontVector = objectToFollow->frontVector;
        position = objectToFollow->position;
        moveObject(7.0f);

        glm::vec3 rightVector = glm::normalize(glm::cross(frontVector, upVector));

        position += glm::normalize(glm::cross(frontVector, rightVector)) * -2.0f;
        pitch = -35.0f;
    }

    void Camera::followTheObject(Object *object) {
        objectToFollow = object;
        follow();
    }

} // world
