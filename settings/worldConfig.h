//
// Created by dima on 22.08.22.
//

#ifndef SOULSLIKEGL_WORLDCONFIG_H
#define SOULSLIKEGL_WORLDCONFIG_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <map>

namespace world {
    struct ObjectState {
        float yaw;
        float pitch;
        float roll;
        glm::vec3 position;
    };
}

namespace settings {
    const struct {
        const glm::vec3 objectPositions[10];
        world::ObjectState cameraInitialState {
            90.0f,
            0.0f,
            0.0f,
            glm::vec3(0.0f, 0.0f, 3.0f)
        };
        const float cameraFow = 45.0f;
        const float mouseSensitivity = 0.1f;
        const float objectSpeed = 2.5f;
        const float rotateSpeed = 125.0f;
        const struct objectSettingsStruct {
            float yaw = 90.0f;
            float pitch = 0;
            float fov = 45;
            float sensitivity = 0.1f;
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
        } cameraSettings;
    } testWorld {
            .objectPositions = {
                    glm::vec3(-4.0f, 0.0f, 0.0f),
                    glm::vec3(-2.0f, 0.0f, 2.0f),
                    glm::vec3(0.0f, 0.0f, 2.0f),
                    glm::vec3(2.0f, 0.0f, 2.0f),
                    glm::vec3(-2.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(2.0f, 0.0f, 0.0f),
                    glm::vec3(-2.0f, 0.0f, -2.0f),
                    glm::vec3(0.0f, 0.0f, -2.0f),
                    glm::vec3(2.0f, 0.0f, -2.0f)
            }
    };
}

#endif //SOULSLIKEGL_WORLDCONFIG_H
