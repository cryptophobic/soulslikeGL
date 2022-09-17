#ifndef SOULSLIKEGL_CONTROLS_H
#define SOULSLIKEGL_CONTROLS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>

namespace settings {

    enum ActionList : unsigned int {
        moveForward = 1, moveBackward, rotateLeft, rotateRight, strafeLeft, strafeRight, freeRotate, zoom, switchObject
    };

    const std::map<int, ActionList> sceneInputSettings{
            {GLFW_KEY_TAB, ActionList::switchObject}
    };

    const std::map<int, ActionList> objectInputSettings{
            {GLFW_KEY_DOWN, ActionList::moveBackward},
            {GLFW_KEY_UP, ActionList::moveForward},
            {GLFW_KEY_LEFT, ActionList::rotateLeft},
            {GLFW_KEY_RIGHT, ActionList::rotateRight},
    };

    const std::map<int, ActionList> cameraInputSettings{
            {GLFW_KEY_S, ActionList::moveBackward},
            {GLFW_KEY_W, ActionList::moveForward},
            {GLFW_KEY_A, ActionList::strafeLeft},
            {GLFW_KEY_D, ActionList::strafeRight},
    };
}
#endif //SOULSLIKEGL_CONTROLS_H
