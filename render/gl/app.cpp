//
// Created by dima on 11.08.22.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app.h"
#include "../../engine/Controller.h"
#include "common/Texture.h"
#include "common/Shader.h"
#include "../../settings/config.h"
#include "../../utils/filesystem_helper.h"
#include "../../settings/worldConfig.h"
#include "SceneRenderer.h"
#include <stdexcept>
#include <array>

engine::Controller controller;
GLFWwindow *window = nullptr;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

namespace render {

    SceneRenderer sceneRenderer;

    void App::start(int argc, char *argv[]) {

        FileSystemHelper::setApplicationPath(std::string(argv[0]));

        glfw_create_window();
        glad_init();

        set_mouse_position_callback();
        set_scroll_callback();
        set_framebuffer_size_callback();
        set_key_callback();

        set_scene();

        event_loop();
        terminate();
    }

    void App::set_scene() {
        auto scene = controller.getCurrentScene();
        sceneRenderer.set(scene);
    }

    void App::process_input() {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        glm::vec3 movingDirection = controller.cameraFront;
        movingDirection[1] = 0.0f;

        const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            controller.cameraPos += cameraSpeed * movingDirection;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            controller.cameraPos -= cameraSpeed * movingDirection;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            controller.cameraPos -= glm::normalize(glm::cross(controller.cameraFront, controller.cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            controller.cameraPos += glm::normalize(glm::cross(controller.cameraFront, controller.cameraUp)) * cameraSpeed;

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void App::event_loop() {
        while(!glfwWindowShouldClose(window)) {
            auto currentFrame = (float) glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // input
            App::process_input();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 view;
            view = glm::lookAt(controller.cameraPos, controller.cameraPos + controller.cameraFront, controller.cameraUp);
            glm::mat4 projection;
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            projection = glm::perspective(glm::radians((float)controller.fov), (float) width / (float) height, 0.1f, 100.0f);

            sceneRenderer.draw(view, projection);

            // check and call events and swap the buffers
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }

    void App::set_key_callback() {
        glfwSetKeyCallback(window, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
                controller.selectNextObject();
            }
        });
    }

    void App::set_mouse_position_callback() {
        glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPos, double yPos) {
            controller.mousePositionCallback(xPos, yPos);
        });
    }

    void App::set_scroll_callback() {
        glfwSetScrollCallback(window, [](GLFWwindow *window, double xOffset, double yOffset) {
            controller.scrollCallback(xOffset, yOffset);
        });
    }

    void App::set_framebuffer_size_callback() {
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
            // TODO: looks ugly
            std::array<int, 4> viewport = controller.getViewportVector(width, height);
            glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
        });
    }

    void App::glad_init() {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
        glEnable(GL_DEPTH_TEST);
    }

    void App::terminate() {
        glfwTerminate();
    }

    void App::glfw_create_window() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(
                settings::screen.resolution.width,
                settings::screen.resolution.height,
                settings::window.title, nullptr, nullptr);
        if (window == nullptr) {
            terminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}
