//
// Created by dima on 11.08.22.
//

//TODO: all the OpenGL must be isolated in init/glfw
//#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Controller.h"
#include "../init.h"
#include "../common/Shader.h"
#include "../common/Texture.h"
#include "../objects/cube.h"

using namespace init;

namespace engine {

    void engine::Controller::mouseCallback(double xPos, double yPos) {

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

    void Controller::framebufferSizeCallback(int width, int height) {
        Init::set_viewport_size(0, 0, width, height);
    }

    void Controller::run() {
        Init::set_mouse_position_callback();
        Init::set_scroll_callback();
        Init::set_framebuffer_size_callback();

        common::Shader shaderProgram("../shaders/shader.vert", "../shaders/shader.frag");
        common::Texture textureContainer("../textures/container.jpg");
        common::Texture textureFace("../textures/awesomeface.png", GL_RGBA);

        Init::load_VAO_VBO();

        shaderProgram.use();
        shaderProgram.setInt("texture1", 0); // or with shader class
        shaderProgram.setInt("texture2", 1); // or with shader class

        Init::enable_gl_depth_test();
        Init::event_loop(textureContainer, textureFace, shaderProgram);
        Init::terminate();
    }
} // engine