#include "SceneV2.h"
#include "Camera.h"
#include "../settings/config.h"
#include "../settings/controls.h"
#include "abilities/Move.h"

namespace world {

    SceneV2::SceneV2() {
        sceneControls = settings::sceneInputSettings;
        camera = new Camera(++lastObjectId, settings::testWorld.cameraInitialState);
        objects.emplace_back(camera);
        updateControlsMap();
    }

    void SceneV2::putNewObject(const std::vector<float> *vertices, glm::vec3 position) {
        std::unique_ptr<FunctionalObject> functionalObject(new FunctionalObject());
        functionalObject->object = std::make_unique<Object>(
                ++lastObjectId,
                ObjectState{0.0f, 0.0f, 0.0f, position});

        functionalObject->object->objectGeometry = new ObjectGeometry(*vertices);
        functionalObject->abilities.emplace_back(
                std::make_unique<abilities::Move>(functionalObject->object.get()));
        //object->behaviour = new abilities::Move(object);
        if (currentObject == nullptr) {
            // TODO: use smart pointer
            setCurrentObject(functionalObject->object.get());
//            {GLFW_KEY_DOWN, world::Object::ActionList::moveBackward},
//            {GLFW_KEY_UP, world::Object::ActionList::moveForward},
//            {GLFW_KEY_LEFT, world::Object::ActionList::rotateLeft},
//            {GLFW_KEY_RIGHT, world::Object::ActionList::rotateRight},

            onKeyDownActionMethods[386] =
                    [ObjectPtr = (abilities::Move *)functionalObject->abilities[0].get()]
                    {
                        ObjectPtr->enqueueMoveBackward();
                    };
        }
        functionalObjects.emplace_back(std::move(functionalObject));
    }

    void SceneV2::setCurrentObject(Object *object) {
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

    void SceneV2::updateControlsMap() {
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

    void SceneV2::switchObjectMethod() {
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

    void SceneV2::keyDownAction(unsigned int action) {
        if (onKeyDownActionMethods.contains(action)) {
            return onKeyDownActionMethods[action]();
        }
        unsigned int objectId = action / OBJECT_CONTROLS_OFFSET;
        action -= (objectId * OBJECT_CONTROLS_OFFSET);
        if (objectId == currentObject->objectId) {
            return currentObject->keyDownAction((Object::ActionList) action);
        }
        if (objectId == camera->objectId) {
            return camera->keyDownAction((Camera::ActionList) action);
        }
    }

    void SceneV2::keyPressedAction(unsigned int action) {
        if (onKeyPressedActionMethods.contains(action)) {
            return ((*this).*(onKeyPressedActionMethods[action]))();
        }
        unsigned int objectId = action / OBJECT_CONTROLS_OFFSET;
        if (objectId == currentObject->objectId) {
            return currentObject->keyPressedAction((Object::ActionList) action);
        }
        if (objectId == camera->objectId) {
            return camera->keyPressedAction((Camera::ActionList) action);
        }
    }

    void SceneV2::processState() {
        for (auto object: objects) {
            // Camera must be processed the last
            // TODO: Code smells bad
            if (object->objectId == camera->objectId) continue;
            functionalObjects[0]->abilities[0]->execute();
            object->executeActions();
        }
        camera->executeActions();

        // TODO: sort this out
        lastX = lastXCandidate;
        lastY = lastYCandidate;
    }

    void SceneV2::mouseMoveAction(double xPos, double yPos) {

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
