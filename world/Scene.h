//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_SCENE_H
#define SOULSLIKEGL_SCENE_H

#include <glm/glm.hpp>
#include <map>
#include <functional>
#include <memory>
#include "ObjectGeometry.h"
#include "Object.h"
#include "Camera.h"
#include "abilities/Ability.h"

#define OBJECT_CONTROLS_OFFSET 128

namespace world {

    struct FunctionalObject {
        std::vector<std::unique_ptr<abilities::Ability>> abilities{};
        std::unique_ptr<Object> object = nullptr;
    };

    class Scene {
    public:
        Scene();
        std::vector<std::unique_ptr<FunctionalObject>> functionalObjects{};
        std::vector<Object*> objects{};
        Camera *camera;
        Object *currentObject = nullptr;
        void putNewObject(const std::vector<float> *vertices, glm::vec3 position);
        void setCurrentObject(Object *);
        void keyPressedAction(unsigned int);
        void keyDownAction(unsigned int);
        void mouseMoveAction(double xPos, double yPos);
        void switchObjectMethod();
        void processState();
        std::map<int /** keycode **/, unsigned int /** action **/> controls;

        enum ActionList : unsigned int {switchObject = 1};

    private:
        void updateControlsMap();
        // TODO: sort this out
        double lastX = 0, lastY = 0, lastXCandidate = 0, lastYCandidate = 0;
        bool firstMouse = true;

        std::map<int, ActionList> sceneControls;
        std::map<unsigned int, std::function<void()>> onKeyDownActionMethods {
        };

        std::map<unsigned int, void (Scene::*)()> onKeyPressedActionMethods {
                {ActionList::switchObject, &Scene::switchObjectMethod}
        };
        unsigned int lastObjectId = 1;
    };

} // world

#endif //SOULSLIKEGL_SCENE_H
