//
// Created by dima on 15.08.22.
//

#include <iostream>
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
            for (auto const &[key, action]: currentObject->object->controls) {
                controls[key] = OBJECT_CONTROLS_OFFSET * currentObject->objectId + action;
            }
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

    void Scene::onKeyDownAction(unsigned int action) {
        if (onKeyDownActionMethods.contains(action)) {
            ((*this).*(onKeyDownActionMethods[action]))();
        } else {
            // Object onkeydown invocation
        }
    }

    void Scene::onKeyPressedAction(unsigned int action) {
        if (onKeyPressedActionMethods.contains(action)) {
            ((*this).*(onKeyPressedActionMethods[action]))();
        } else {
            unsigned int objectId = action / OBJECT_CONTROLS_OFFSET;
            if (currentObject != nullptr && currentObject->objectId == objectId) {
                action -= objectId * OBJECT_CONTROLS_OFFSET;
                currentObject->object->onKeyPressedAction((Object::ActionList) action);
            }
            // Object onkeydown invocation
        }
    }

    void Scene::processState(const float objectSpeed) {
        for (auto worldObject: objects) {
            unsigned int objectMovingState = worldObject->object->getMovingState();
            if (objectMovingState != 0) {
                if (objectMovingState & SOULSLIKEGL_MOVE_FORWARD) {
                    glm::vec3 movingDirection = worldObject->direction;
                    //movingDirection[1] = 0.0f;

                    worldObject->position += objectSpeed * movingDirection;

                    worldObject->object->stopMoving(SOULSLIKEGL_MOVE_FORWARD);
                }
                if (objectMovingState & SOULSLIKEGL_MOVE_BACKWARD) {
                    glm::vec3 movingDirection = worldObject->direction;
                    //movingDirection[1] = 0.0f;

                    worldObject->position -= objectSpeed * movingDirection;

                    worldObject->object->stopMoving(SOULSLIKEGL_MOVE_BACKWARD);
                }
                if (objectMovingState & SOULSLIKEGL_ROTATE_RIGHT) {
                    worldObject->rotateObject(-objectSpeed);

                    worldObject->object->stopMoving(SOULSLIKEGL_ROTATE_RIGHT);
                }
                if (objectMovingState & SOULSLIKEGL_ROTATE_LEFT) {
                    worldObject->rotateObject(objectSpeed);

                    worldObject->object->stopMoving(SOULSLIKEGL_ROTATE_LEFT);
                }
            }
        }
    }
} // world
