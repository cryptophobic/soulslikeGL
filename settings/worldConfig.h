//
// Created by dima on 22.08.22.
//

#ifndef SOULSLIKEGL_WORLDCONFIG_H
#define SOULSLIKEGL_WORLDCONFIG_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <map>
#include "../world/Scene.h"

namespace settings {
    const struct {
        const glm::vec3 objectPositions[10];
        const struct {
            float yaw = -90.0f;
            float pitch = 0;
            float fov = 45;
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
        } cameraSettings;
    } testWorld {
            .objectPositions = {
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(2.0f, 5.0f, -15.0f),
                    glm::vec3(-1.5f, -2.2f, -2.5f),
                    glm::vec3(-3.8f, -2.0f, -12.3f),
                    glm::vec3(2.4f, -0.4f, -3.5f),
                    glm::vec3(-1.7f, 3.0f, -7.5f),
                    glm::vec3(1.3f, -2.0f, -2.5f),
                    glm::vec3(1.5f, 2.0f, -2.5f),
                    glm::vec3(1.5f, 0.2f, -1.5f),
                    glm::vec3(-1.3f, 1.0f, -1.5f)
            }
    };

    const std::map<int, world::Scene::ActionList> sceneInputSettings{
            {GLFW_KEY_TAB, world::Scene::ActionList::switchObject}
    };

    const std::map<int, world::Object::ActionList> objectInputSettings{
            {GLFW_KEY_DOWN, world::Object::ActionList::moveBackward},
            {GLFW_KEY_UP, world::Object::ActionList::moveForward},
            {GLFW_KEY_LEFT, world::Object::ActionList::rotateLeft},
            {GLFW_KEY_RIGHT, world::Object::ActionList::rotateRight},
    };

    const std::map<int, world::Object::ActionList> cameraInputSettings{
            {GLFW_KEY_S, world::Object::ActionList::moveBackward},
            {GLFW_KEY_W, world::Object::ActionList::moveForward},
            {GLFW_KEY_A, world::Object::ActionList::strafeLeft},
            {GLFW_KEY_D, world::Object::ActionList::strafeRight},
    };
}

#endif //SOULSLIKEGL_WORLDCONFIG_H
