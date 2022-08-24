//
// Created by dima on 11.08.22.
//

#include <glm/gtc/matrix_transform.hpp>

#include <array>
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
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw += xOffset;
        pitch += yOffset;

        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;

        glm::vec3 direction;
        direction.x = (float) cos((glm::radians(yaw)) * cos(glm::radians(pitch)));
        direction.y = (float) sin(glm::radians(pitch));
        direction.z = (float) (sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

        cameraFront = glm::normalize(direction);
    }

    void Controller::scrollCallback(double xOffset, double yOffset) {
        fov -= (float) yOffset;
        if (fov < 1.0f) fov = 1.0f;
        if (fov > 45.0f) fov = 45.0f;
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

    void Controller::selectNextObject() {
        bool next = false;
        for (auto worldObject: scene->objects) {
            if (next) {
                scene->setCurrentObject(worldObject);
                next = false;
                break;
            }
            if (worldObject == scene->currentObject) {
                next = true;
            }
        }
        if (next) {
            scene->setCurrentObject(scene->objects[0]);
        }
    }
} // engine