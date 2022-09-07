//
// Created by dima on 11.08.22.
//

#include <glm/gtc/matrix_transform.hpp>

#include <array>
#include <iostream>
#include "Controller.h"
#include "../settings/worldConfig.h"
#include "../objects/cube.h"

namespace engine {

    void engine::Controller::mousePositionCallback(double xPos, double yPos) {

        if (firstMouse) {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        double xOffset = xPos - lastX;
        double yOffset = lastY - yPos;

        lastX = xPos;
        lastY = yPos;

        const float sensitivity = 0.1f;
        xOffset *= -sensitivity;
        yOffset *= sensitivity;

        scene->camera->state.yaw += (float)xOffset;
        scene->camera->state.pitch += (float)yOffset;

        if(scene->camera->state.pitch > 89.0f) scene->camera->state.pitch = 89.0f;
        if(scene->camera->state.pitch < -89.0f) scene->camera->state.pitch = -89.0f;

        scene->camera->updateDirection();
    }

    void Controller::scrollCallback(double xOffset, double yOffset) {
        scene->camera->state.fov -= (float) yOffset;
        if (scene->camera->state.fov < 1.0f) scene->camera->state.fov = 1.0f;
        if (scene->camera->state.fov > 45.0f) scene->camera->state.fov = 45.0f;
    }

    std::array<int, 4> Controller::getViewportVector(int width, int height) {
        return {0, 0, width, height};
    }

    world::Scene *Controller::getCurrentScene() {
        if (scene == nullptr) {
            scene = new world::Scene();
            for (glm::vec3 objectPosition: settings::testWorld.objectPositions) {
                scene->putNewObject(&objects::cube_vertices, objectPosition);
            }
        }
        return scene;
    }

} // engine
