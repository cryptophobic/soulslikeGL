//
// Created by dima on 15.08.22.
//

#include "Scene.h"
#include "../settings/config.h"
#include "../settings/worldConfig.h"

namespace world {

    void Scene::putNewObject(const std::vector<float> *vertices, glm::vec3 position) {
        auto object = new Object(*vertices);
        auto worldObject = new WorldObject();
        worldObject->object = object;
        worldObject->position = position;
        worldObject->objectId = ++lastObjectId;
        objects.emplace_back(worldObject);
        if (currentObject == nullptr) {
            setCurrentObject(worldObject);
        }
    }

    void Scene::setCurrentObject(WorldObject *worldObject) {
        if (currentObject != nullptr) {
            currentObject->object->fragmentShaderPath = settings::rendering.fragmentShaderDefaultPAth;
            currentObject->object->dirty = true;
        }
        currentObject = worldObject;
        currentObject->object->fragmentShaderPath = settings::rendering.fragmentShaderSelectedPAth;
        currentObject->object->dirty = true;
    }

    Scene::Scene() {
       actions = settings::sceneInputSettings;
    }
} // world