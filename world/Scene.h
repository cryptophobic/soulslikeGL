//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_SCENE_H
#define SOULSLIKEGL_SCENE_H

#include <glm/glm.hpp>
#include "Object.h"

namespace world {

    struct worldObject{
        glm::vec3 position;
        float xAngle;
        float yAngle;
        float zAngle;
        Object* object;
        int objectId;
    };


    class Scene {
    public:
        std::vector<worldObject*> objects;
        void putNewObject(std::vector<float> *vertices, glm::vec3 position);
    private:
        unsigned int lastObjectId = 0;
    };

} // world

#endif //SOULSLIKEGL_SCENE_H
