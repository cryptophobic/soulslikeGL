#include <iostream>
#include "Scene.h"
#include "Camera.h"
#include "../settings/worldConfig.h"
#include "../settings/config.h"

namespace world {

    Scene::Scene() {
        sceneControls = settings::sceneInputSettings;
        camera = new Camera(++lastObjectId, settings::testWorld.cameraInitialState);
        objects.emplace_back(camera);
        updateControlsMap();
    }

    void Scene::putNewObject(const std::vector<float> *vertices, glm::vec3 position) {
        auto object = new Object(++lastObjectId, ObjectState{0.0f, 0.0f, 0.0f, position});
        object->objectGeometry = new ObjectGeometry(*vertices);
        objects.emplace_back(object);
        if (currentObject == nullptr) {
            setCurrentObject(object);
        }
    }

    void Scene::setCurrentObject(Object *object) {
        if (currentObject != nullptr) {
            currentObject->objectGeometry->fragmentShaderPath = settings::rendering.fragmentShaderDefaultPAth;
            currentObject->objectGeometry->dirty = true;
        }
        currentObject = object;
        currentObject->objectGeometry->fragmentShaderPath = settings::rendering.fragmentShaderSelectedPAth;
        currentObject->objectGeometry->dirty = true;
        updateControlsMap();
        camera->bindToTheObject(object);
    }

    void Scene::updateControlsMap() {
        if (currentObject != nullptr) {
            for (auto const &[key, action]: currentObject->controls) {
                controls[key] = OBJECT_CONTROLS_OFFSET * currentObject->objectId + action;
            }
        }

        for (auto const &[key, action]: camera->controls) {
            controls[key] = OBJECT_CONTROLS_OFFSET * camera->objectId + action;
        }

        for (auto const& [key, action] : sceneControls) {
            controls[key] = action;
        }
    }

    void Scene::switchObjectMethod() {
        if (objects.empty()) {
            return;
        }
        bool next = false;
        for (auto object: objects) {
            if (object->objectId == camera->objectId) continue;
            if (next) {
                setCurrentObject(object);
                next = false;
                break;
            }
            if (object == currentObject) {
                next = true;
            }
        }
        if (next) {
            setCurrentObject(objects[0]->objectId == camera->objectId ? objects[1] : objects[0]);
        }
    }

    void Scene::action(unsigned int action) {
        if (onActionMethods.contains(action)) {
            ((*this).*(onActionMethods[action]))();
        } else {
            unsigned int objectId = action / OBJECT_CONTROLS_OFFSET;
            Object *object =
                    currentObject->objectId == objectId ? currentObject :
                    camera->objectId == objectId ? camera : nullptr;

            if (object != nullptr) {
                action -= objectId * OBJECT_CONTROLS_OFFSET;
                object->action((Object::ActionList) action);
            }
        }
    }

    void Scene::processState(const float objectSpeed) {
        for (auto object: objects) {
            unsigned int objectMovingState = object->getMovingState();
            if (objectMovingState != 0) {
                object->move(objectSpeed, objectSpeed * 50);
                camera->follow();
            }
        }
    }
} // world
