//
// Created by dima on 27.08.22.
//

#ifndef SOULSLIKEGL_WORLDOBJECT_H
#define SOULSLIKEGL_WORLDOBJECT_H

#include <glm/glm.hpp>
#include "Object.h"

namespace world {

    class WorldObject {
    public:
        WorldObject();
        void rotateObject(float objectSpeed);
        void moveObject(float objectSpeed);
        glm::vec3 position;
        float xAngle = 0.0f;
        float yaw = 0.0f;
        float zAngle = 0.0f;
        Object* object;
        double pitch = 0, fov = 45;
        glm::vec3 direction;

        unsigned int objectId;
    private:
        void updateDirection();
    };

} // world

#endif //SOULSLIKEGL_WORLDOBJECT_H
