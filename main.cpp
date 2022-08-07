#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common/Shader.h"
#include "common/Texture.h"
#include "objects/cube.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow* screen_init();


float degrees = 0.0f;
float xtrans = 0.5f;
float iterator = 0.05f;

int main()
{
    GLFWwindow* window = screen_init();
    common::Shader shaderProgram("../shaders/shader.vert", "../shaders/shader.frag");
    common::Texture textureContainer("../textures/container.jpg");
    common::Texture textureFace("../textures/awesomeface.png", GL_RGBA);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objects::cube_vertices), objects::cube_vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shaderProgram.use();
    shaderProgram.setInt("texture1", 0); // or with shader class
    shaderProgram.setInt("texture2", 1); // or with shader class

    while(!glfwWindowShouldClose(window)) {
        // input
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0); // activate texture unit first
        glBindTexture(GL_TEXTURE_2D, textureContainer.ID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureFace.ID);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view = glm::mat4(1.0f);
        // note that we’re translating the scene in the reverse direction
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,100.0f);

        GLint modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        GLint viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        GLint projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        shaderProgram.use();

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

GLFWwindow* screen_init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "Murka Window", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        // TODO: error rising return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        // TODO: error rising return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
//    int length = width > height ? height : width;
//    int x = width > height ? (width - length) / 2 : 0;
//    int y = height > width ? (height - length) / 2 : 0;
//    glViewport(x, y, length, length);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        xtrans += iterator;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        xtrans -= iterator;
    }

    if (xtrans >= 0.5 || xtrans <= -0.5) {
        xtrans = xtrans >= 0.5f ? 0.49f : -0.49f;
        iterator = -iterator;
    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        degrees = degrees + 1.0f >= 360.0f ? 0.0f : degrees + 1.0f;
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        degrees = degrees - 1.0f <= 0.0f ? 360.0f : degrees - 1.0f;
    }
}