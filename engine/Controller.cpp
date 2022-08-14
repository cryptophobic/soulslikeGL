//
// Created by dima on 11.08.22.
//

//TODO: all the OpenGL must be isolated in render/glfw
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <array>
#include "Controller.h"
#include "../init.h"
#include "../common/Shader.h"
#include "../common/Texture.h"
#include "../objects/cube.h"

using namespace render;

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

//        glm::vec3 direction;
//        direction.x = (float) cos((glm::radians(yaw)) * cos(glm::radians(pitch)));
//        direction.y = (float) sin(glm::radians(pitch));
//        direction.z = (float) (sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
//
//        cameraFront = glm::normalize(direction);
    }

    void Controller::scrollCallback(double xOffset, double yOffset) {
        fov -= (float) yOffset;
        if (fov < 1.0f) fov = 1.0f;
        if (fov > 45.0f) fov = 45.0f;
    }

    std::array<int, 4> Controller::getViewportVector(int width, int height) {
        return {0, 0, width, height};
    }

    void Controller::run() {
//        App::set_mouse_position_callback();
//        App::set_scroll_callback();
//        App::set_framebuffer_size_callback();

        App::set_shaders();
        App::set_textures();

        App::event_loop();

        App::terminate();
    }
} // engine