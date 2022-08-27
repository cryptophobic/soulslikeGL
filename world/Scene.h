//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_SCENE_H
#define SOULSLIKEGL_SCENE_H

#include <glm/glm.hpp>
#include <map>
#include <functional>
#include "Object.h"

#define OBJECT_CONTROLS_OFFSET 128

namespace world {

    struct WorldObject{
        glm::vec3 position;
        float xAngle = 0.0f;
        float yAngle = 0.0f;
        float zAngle = 0.0f;
        Object* object;
        unsigned int objectId;
    };

    class Scene {
    public:
        Scene();
        std::vector<WorldObject*> objects;
        WorldObject *currentObject;
        void putNewObject(const std::vector<float> *vertices, glm::vec3 position);
        void setCurrentObject(WorldObject *);
        void keyDownOnAction(unsigned int);
        void switchObjectMethod();
        std::map<unsigned int, unsigned int> controls;

        enum ActionList : unsigned int {switchObject};

    private:
        void updateControlsMap();
        std::map<unsigned int, ActionList> sceneControls;
        std::map<unsigned int, void (Scene::*)()> onKeyDownActionMethods {
                {ActionList::switchObject, &Scene::switchObjectMethod}
        };
        std::map<unsigned int, void (Scene::*)()> onKeyPressedActionMethods {};
        unsigned int lastObjectId = 0;
    };

} // world

#endif //SOULSLIKEGL_SCENE_H
