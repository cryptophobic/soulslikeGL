//
// Created by dima on 11.08.22.
//

#ifndef SOULSLIKEGL_CONTROLLER_H
#define SOULSLIKEGL_CONTROLLER_H

#include <array>
#include "../world/Scene.h"

namespace engine {

    class Controller {
    public:
        void mousePositionCallback(double xPos, double yPos);
        void scrollCallback(double xOffset, double yOffset);
        std::array<int, 4> getViewportVector(int width, int height);
        world::Scene *getCurrentScene();

        double lastX = 400, lastY = 300;
        double yaw = -90.0f, pitch = 0, fov = 45;
        bool firstMouse = true;

        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    private:
        world::Scene *scene;

    };

} // engine

#endif //SOULSLIKEGL_CONTROLLER_H
