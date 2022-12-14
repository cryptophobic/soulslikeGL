#include "Camera.h"
#include "../settings/controls.h"

namespace world {

    Camera::Camera(unsigned int newObjectId, ObjectState initialState) :
        Object(newObjectId, initialState),
        fov(settings::testWorld.cameraFow)
    {
        display = false;
        controls = settings::cameraInputSettings;
        onKeyDownActionMethods = {
                {settings::ActionList::moveForward, &Camera::moveForwardMethod},
                {settings::ActionList::moveBackward, &Camera::moveBackwardMethod},
                {settings::ActionList::strafeLeft, &Camera::strafeLeftMethod},
                {settings::ActionList::strafeRight, &Camera::strafeRightMethod},
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
