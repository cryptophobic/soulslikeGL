//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_SCENE_H
#define SOULSLIKEGL_SCENE_H

#include <glm/glm.hpp>
#include "Object.h"

namespace world {

    struct WorldObject{
        glm::vec3 position;
        float xAngle = 0.0f;
        float yAngle = 0.0f;
        float zAngle = 0.0f;
        Object* object;
        unsigned int objectId;
    };


    class Scene {
    public:
        std::vector<WorldObject*> objects;
        WorldObject *currentObject;
        void putNewObject(const std::vector<float> *vertices, glm::vec3 position);
        void setCurrentObject(WorldObject *);
    private:
        unsigned int lastObjectId = 0;
    };

} // world

#endif //SOULSLIKEGL_SCENE_H
