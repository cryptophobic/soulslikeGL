#include <iostream>
#include "Scene.h"
#include "Camera.h"
#include "../settings/config.h"
#include "../settings/worldConfig.h"

namespace world {

    Scene::Scene() {
        sceneControls = settings::sceneInputSettings;
        currentObject = nullptr;
        camera = new Camera();
        camera->pitch = settings::testWorld.cameraSettings.pitch;
        camera->yaw = settings::testWorld.cameraSettings.yaw;
        camera->fov = settings::testWorld.cameraSettings.fov;
        camera->position = settings::testWorld.cameraSettings.position;
        camera->objectId = ++lastObjectId;
        camera->updateDirection();

        updateControlsMap();
    }

    void Scene::putNewObject(const std::vector<float> *vertices, glm::vec3 position) {
        auto object = new Object();
        object->objectGeometry = new ObjectGeometry(*vertices);
        object->position = position;
        object->updateDirection();
        object->objectId = ++lastObjectId;
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
        camera->followTheObject(object);
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
            setCurrentObject(objects[0]);
        }
    }

    void Scene::onKeyDownAction(unsigned int action) {
        if (onKeyDownActionMethods.contains(action)) {
            ((*this).*(onKeyDownActionMethods[action]))();
        } else {
            unsigned int objectId = action / OBJECT_CONTROLS_OFFSET;
            if (currentObject != nullptr && currentObject->objectId == objectId) {
                action -= objectId * OBJECT_CONTROLS_OFFSET;
                currentObject->onKeyDownAction((Object::ActionList) action);
            }
            if (camera != nullptr && camera->objectId == objectId) {
                action -= objectId * OBJECT_CONTROLS_OFFSET;
                camera->onKeyDownAction((Camera::ActionList) action);
            }
        }
    }

    void Scene::onKeyPressedAction(unsigned int action) {
        if (onKeyPressedActionMethods.contains(action)) {
            ((*this).*(onKeyPressedActionMethods[action]))();
        } else {
            unsigned int objectId = action / OBJECT_CONTROLS_OFFSET;
            if (currentObject != nullptr && currentObject->objectId == objectId) {
                action -= objectId * OBJECT_CONTROLS_OFFSET;
                currentObject->onKeyPressedAction((Object::ActionList) action);
                if (camera != nullptr
                    && camera->objectToFollow != nullptr
                    && camera->objectToFollow->objectId == currentObject->objectId) {
                    camera->follow();
                }
            }
            if (camera != nullptr && camera->objectId == objectId) {
                action -= objectId * OBJECT_CONTROLS_OFFSET;
                camera->onKeyPressedAction((Camera::ActionList) action);
            }
        }
    }

    void Scene::processState(const float objectSpeed) {
        for (auto object: objects) {
            unsigned int objectMovingState = object->getMovingState();
            if (objectMovingState != 0) {
                object->move(objectSpeed, objectSpeed * 50);
            }
        }
        if (camera->getMovingState() != 0) {
            camera->move(objectSpeed, objectSpeed * 50);
        }
    }
} // world
