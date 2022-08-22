//
// Created by dima on 15.08.22.
//

#include "Scene.h"

namespace world {
    void Scene::putNewObject(const std::vector<float> *vertices, glm::vec3 position) {
        auto object = new Object(*vertices);
        auto worldObject = new WorldObject();
        worldObject->object = object;
        worldObject->position = position;
        worldObject->objectId = ++lastObjectId;
        objects.push_back(worldObject);
    }
} // world