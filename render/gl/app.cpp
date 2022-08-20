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
#include "../../objects/cube.h"
#include "../../settings/config.h"
#include "../../utils/filesystem_helper.h"
#include "../../objects/square.h"
#include <stdexcept>
#include <array>

engine::Controller controller;
GLFWwindow *window = nullptr;

unsigned int VBO, VAO;
common::Shader shaderProgram;
common::Texture textureContainer;
common::Texture textureFace;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

double yaw = -90.0f, pitch = 0, fov = 45;

glm::vec3 cubePositions[] = {
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
};



namespace render {
    void App::start(int argc, char *argv[]) {

        FileSystem::setApplicationPath(std::string(argv[0]));

        glfw_create_window();
        glad_init();

        set_mouse_position_callback();
        set_scroll_callback();
        set_framebuffer_size_callback();
        set_scene();

        //App::event_loop();

        controller.run();
    }

    void App::set_scene() {
        controller.getCurrentScene();
    }

    void App::set_shaders() {
        shaderProgram.set(FileSystem::getPath("shaders/shader.vert").c_str(), FileSystem::getPath("shaders/shader.frag").c_str());
    }

    void App::set_textures() {
        textureContainer.set(FileSystem::getPath("textures/container.jpg").c_str());
        textureFace.set(FileSystem::getPath("textures/awesomeface.png").c_str(), GL_RGBA);
    }

    void App::process_input() {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        glm::vec3 movingDirection = cameraFront;
        movingDirection[1] = 0.0f;

        const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * movingDirection;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * movingDirection;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void App::event_loop() {

//        std::vector<GLfloat> vertexData(
//                objects::cube_vertices,
//                objects::cube_vertices + sizeof objects::cube_vertices / sizeof objects::cube_vertices[0]
//                );

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (objects::cube_vertices.size() * sizeof(GLfloat)), objects::cube_vertices.data(), GL_STATIC_DRAW);

        //glBufferData(GL_ARRAY_BUFFER, sizeof(objects::cube_vertices), objects::cube_vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        shaderProgram.use();
        shaderProgram.setInt("texture1", 0); // or with shader class
        shaderProgram.setInt("texture2", 1); // or with shader class
        glActiveTexture(GL_TEXTURE0); // activate texture unit first
        glBindTexture(GL_TEXTURE_2D, textureContainer.ID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureFace.ID);

        while(!glfwWindowShouldClose(window)) {
            auto currentFrame = (float) glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // input
            App::process_input();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            const float radius = 10.0f;
            glm::mat4 view;
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

            glm::mat4 projection;
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            projection = glm::perspective(glm::radians((float)fov), (float) width / (float) height    , 0.1f, 100.0f);

            for(unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f + angle),glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f + angle * 2),glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f + angle * 3),glm::vec3(1.0f, 0.0f, 0.0f));

                shaderProgram.setMat4("projection", projection);
                shaderProgram.setMat4("view", view);
                shaderProgram.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            // check and call events and swap the buffers
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }

    void App::set_mouse_position_callback() {
        glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPos, double yPos) {
            controller.mousePositionCallback(xPos, yPos);
        });
    }

    void App::set_scroll_callback() {
        glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xOffset, double yOffset) {
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
