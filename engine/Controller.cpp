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

    std::map<int /** keycode **/, unsigned int /** action **/> Controller::getControls() {
        return getCurrentScene()->controls;
    }

    void Controller::keyDownAction(unsigned int action) {
        return getCurrentScene()->keyDownAction(action);
    }

    void Controller::keyPressedAction(unsigned int action) {
        return getCurrentScene()->keyPressedAction(action);
    }

    void Controller::mouseMoveAction(double xPos, double yPos) {
        return getCurrentScene()->mouseMoveAction(xPos, yPos);
    }

    void Controller::scrollCallback(double xOffset, double yOffset) {
        getCurrentScene()->camera->fov -= (float) yOffset;
        if (scene->camera->fov < 1.0f) scene->camera->fov = 1.0f;
        if (scene->camera->fov > 45.0f) scene->camera->fov = 45.0f;
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
