#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common/Shader.h"
#include "common/Texture.h"
#include "images/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow* screen_init();

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float square_vertices[] = {
        // positions          // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
};

unsigned int square_indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

float degrees = 0.0f;
float xtrans = 0.5f;
float iterator = 0.05f;

int main()
{
    GLFWwindow* window = screen_init();
    common::Shader shaderProgram("../shaders/shader.vert", "../shaders/shader.frag");
    common::Texture textureContainer("../textures/container.jpg");
    common::Texture textureFace("../textures/awesomeface.png", GL_RGBA);

    unsigned int VBO[2], VAO[2], EBO[2];
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);
    glGenBuffers(1, &EBO[0]);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shaderProgram.use();
    shaderProgram.setInt("texture1", 0); // or with shader class
    shaderProgram.setInt("texture2", 1); // or with shader class

    glGenVertexArrays(1, &VAO[1]);
    glGenBuffers(1, &VBO[1]);
    glGenBuffers(1, &EBO[1]);

    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);

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

        glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::translate(trans, glm::vec3(xtrans, -0.5f, 0.0f));
        trans = glm::rotate(trans, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(),glm::vec3(0.0f, 1.0f, 0.0f));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

        shaderProgram.use();
        GLint transformLoc = glGetUniformLocation(shaderProgram.ID,"transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO[1]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        glm::mat4 trans2 = glm::mat4(1.0f);
        trans2 = glm::translate(trans2, glm::vec3(-xtrans, 0.5f, 0.0f));
        trans2 = glm::rotate(trans2, glm::radians(degrees), glm::vec3(0.0f, 0.0f, -1.0f));
        trans2 = glm::scale(trans2, glm::vec3(sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime())));

        shaderProgram.use();
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans2));

        glBindVertexArray(VAO[0]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        /**
         * render
         */

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