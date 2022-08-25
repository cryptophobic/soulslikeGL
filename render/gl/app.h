//
// Created by dima on 11.08.22.
//

#ifndef SOULSLIKEGL_GLFW_APP_H
#define SOULSLIKEGL_GLFW_APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "common/Texture.h"
#include "common/Shader.h"
#include "SceneRenderer.h"
#include "../../engine/Controller.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

namespace render {
    class App {
    public:
        static void start(int argc, char* argv[]);
        static void terminate();
        static void process_input();
        static void event_loop();
    private:
        static void set_mouse_position_callback();
        static void set_scroll_callback();
        static void set_framebuffer_size_callback();
        static void set_key_callback();
        static void glfw_create_window();
        static void set_scene();

        static SceneRenderer sceneRenderer;
        static engine::Controller controller;
        static GLFWwindow *window;
        static float lastFrame;
        static float deltaTime;
    };
}



#endif //SOULSLIKEGL_GLFW_APP_H
