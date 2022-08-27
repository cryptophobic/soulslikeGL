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
        std::vector<Object*> objects;
        Camera *camera;
        Object *currentObject;
        void putNewObject(const std::vector<float> *vertices, glm::vec3 position);
        void setCurrentObject(Object *);
        void onKeyDownAction(unsigned int);
        void onKeyPressedAction(unsigned int);
        void switchObjectMethod();
        void processState(float objectSpeed);
        std::map<int /** keycode **/, unsigned int /** action **/> controls;

        enum ActionList : unsigned int {switchObject};

    private:
        void updateControlsMap();
        std::map<int, ActionList> sceneControls;
        std::map<unsigned int, void (Scene::*)()> onKeyDownActionMethods {
                {ActionList::switchObject, &Scene::switchObjectMethod}
        };
        std::map<unsigned int, void (Scene::*)()> onKeyPressedActionMethods {};
        unsigned int lastObjectId = 0;
    };

} // world

#endif //SOULSLIKEGL_SCENE_H
