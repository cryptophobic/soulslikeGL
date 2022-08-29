//
// Created by dima on 27.08.22.
//

#include "Camera.h"
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

        frontVector.x = (float) cos((glm::radians(yaw)) * cos(glm::radians(pitch)));
        frontVector.y = (float) sin(glm::radians(pitch));
        frontVector.z = (float) (sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
        frontVector = glm::normalize(frontVector);
    }

    void Camera::updateDirection() {
        frontVector.x = (float) cos((glm::radians(yaw)) * cos(glm::radians(pitch)));
        frontVector.y = (float) sin(glm::radians(pitch));
        frontVector.z = (float) (sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
        frontVector = glm::normalize(frontVector);
    }

} // world