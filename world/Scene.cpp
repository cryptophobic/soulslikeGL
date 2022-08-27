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
        updateControlsMap();
    }

    Scene::Scene() {
        sceneControls = settings::sceneInputSettings;
        currentObject = nullptr;
        updateControlsMap();
    }

    void Scene::updateControlsMap() {
        if (currentObject != nullptr) {
            for (auto const &[key, value]: currentObject->object->getControlsMap()) {
                controls[key] = OBJECT_CONTROLS_OFFSET * currentObject->objectId + value;
            }
        }

        for (auto const& [key, value] : sceneControls) {
            controls[key] = value;
        }
    }

    void Scene::keyDownOnAction(unsigned int action) {
        if (onKeyDownActionMethods.contains(action)) {
            ((*this).*(onKeyDownActionMethods[action]))();
        }
    }

    void Scene::switchObjectMethod() {
        if (objects.empty()) {
            return;
        }
        bool next = false;
        for (auto worldObject: objects) {
            if (next) {
                setCurrentObject(worldObject);
                next = false;
                break;
            }
            if (worldObject == currentObject) {
                next = true;
            }
        }
        if (next) {
            setCurrentObject(objects[0]);
        }
    }
} // world