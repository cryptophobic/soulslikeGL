#include <iostream>
#include "Scene.h"
#include "Camera.h"
#include "../settings/config.h"
#include "../settings/controls.h"

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
        //object->behaviour = new behaviours::Move(object);
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

    void Scene::keyDownAction(unsigned int action) {
        if (onKeyDownActionMethods.contains(action)) {
            return ((*this).*(onKeyDownActionMethods[action]))();
        }
        unsigned int objectId = action / OBJECT_CONTROLS_OFFSET;
        action -= (objectId * OBJECT_CONTROLS_OFFSET);
        if (objectId == currentObject->objectId) {
            return currentObject->keyDownAction((settings::ActionList) action);
        }
        if (objectId == camera->objectId) {
            return camera->keyDownAction((settings::ActionList) action);
        }
    }

    void Scene::keyPressedAction(unsigned int action) {
        if (onKeyPressedActionMethods.contains(action)) {
            return ((*this).*(onKeyPressedActionMethods[action]))();
        }
        unsigned int objectId = action / OBJECT_CONTROLS_OFFSET;
        if (objectId == currentObject->objectId) {
            return currentObject->keyPressedAction((settings::ActionList) action);
        }
        if (objectId == camera->objectId) {
            return camera->keyPressedAction((settings::ActionList) action);
        }
    }

    void Scene::processState() {
        for (auto object: objects) {
            // Camera must be processed the last
            // TODO: Code smells bad
            if (object->objectId == camera->objectId) continue;
            object->executeActions();
        }
        camera->executeActions();

        // TODO: sort this out
        lastX = lastXCandidate;
        lastY = lastYCandidate;
    }

    void Scene::mouseMoveAction(double xPos, double yPos) {

        if (firstMouse) {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        currentObject->freeRotateMethod(xPos, yPos, lastX, lastY);
        // TODO: sort this out
        lastXCandidate = xPos;
        lastYCandidate = yPos;
    }
} // world
