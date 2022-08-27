//
// Created by dima on 27.08.22.
//

#include "WorldObject.h"

namespace world {
    WorldObject::WorldObject() {
        updateDirection();
    }

    void WorldObject::rotateObject(float objectSpeed) {
        yaw += objectSpeed;
        updateDirection();
    }

    void WorldObject::updateDirection() {
        direction.x = (float) cos((glm::radians(-yaw)) * cos(glm::radians(pitch)));
        direction.y = (float) sin(glm::radians(pitch));
        direction.z = (float) (sin(glm::radians(-yaw)) * cos(glm::radians(pitch)));
        direction = glm::normalize(direction);
    }

    void WorldObject::moveObject(float objectSpeed) {
        position -= objectSpeed * direction;
    }


} // world