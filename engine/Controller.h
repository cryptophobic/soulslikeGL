//
// Created by dima on 11.08.22.
//

#ifndef SOULSLIKEGL_CONTROLLER_H
#define SOULSLIKEGL_CONTROLLER_H

namespace engine {

    class Controller {
    public:
        void run();
        void mouseCallback(double xPos, double yPos);
        void scrollCallback(double xOffset, double yOffset);
        void framebufferSizeCallback(int width, int height);
    private:
        double lastX = 400, lastY = 300;
        double yaw = -90.0f, pitch = 0, fov = 45;
        bool firstMouse = true;
        float deltaTime = 0.0f; // Time between current frame and last frame
        float lastFrame = 0.0f; // Time of last frame

//        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    };

} // engine

#endif //SOULSLIKEGL_CONTROLLER_H
