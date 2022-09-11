//
// Created by dmitr on 11.09.2022.
//

#ifndef SOULSLIKEGL_CONTROLS_H
#define SOULSLIKEGL_CONTROLS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include "../world/Camera.h"
#include "../world/Object.h"
#include "../world/Scene.h"


namespace settings {
    const std::map<int, world::Scene::ActionList> sceneInputSettings{
            {GLFW_KEY_TAB, world::Scene::ActionList::switchObject}
    };

    const std::map<int, world::Object::ActionList> objectInputSettings{
            {GLFW_KEY_DOWN, world::Object::ActionList::moveBackward},
            {GLFW_KEY_UP, world::Object::ActionList::moveForward},
            {GLFW_KEY_LEFT, world::Object::ActionList::rotateLeft},
            {GLFW_KEY_RIGHT, world::Object::ActionList::rotateRight},
    };

    const std::map<int, world::Camera::ActionList> cameraInputSettings{
            {GLFW_KEY_S, world::Camera::ActionList::moveBackward},
            {GLFW_KEY_W, world::Camera::ActionList::moveForward},
            {GLFW_KEY_A, world::Camera::ActionList::strafeLeft},
            {GLFW_KEY_D, world::Camera::ActionList::strafeRight},
    };
}
#endif //SOULSLIKEGL_CONTROLS_H
