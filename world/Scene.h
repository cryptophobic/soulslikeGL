//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_SCENE_H
#define SOULSLIKEGL_SCENE_H

#include <glm/glm.hpp>
#include <map>
#include <functional>
#include "ObjectGeometry.h"
#include "Object.h"
#include "Camera.h"

#define OBJECT_CONTROLS_OFFSET 128

namespace world {

    class Scene {
    public:
        Scene();
        std::vector<Object*> objects{};
        Camera *camera;
        Object *currentObject = nullptr;
        void putNewObject(const std::vector<float> *vertices, glm::vec3 position);
        void setCurrentObject(Object *);
        void keyPressedAction(unsigned int);
        void keyDownAction(unsigned int);
        void switchObjectMethod();
        void processState(float objectSpeed);
        std::map<int /** keycode **/, unsigned int /** action **/> controls;

        enum ActionList : unsigned int {switchObject = 1};

    private:
        void updateControlsMap();
        std::map<int, ActionList> sceneControls;
        std::map<unsigned int, void (Scene::*)()> onKeyDownActionMethods {
        };

        std::map<unsigned int, void (Scene::*)()> onKeyPressedActionMethods {
                {ActionList::switchObject, &Scene::switchObjectMethod}
        };
        unsigned int lastObjectId = 1;
    };

} // world

#endif //SOULSLIKEGL_SCENE_H
