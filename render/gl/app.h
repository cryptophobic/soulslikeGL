//
// Created by dima on 11.08.22.
//

#ifndef SOULSLIKEGL_GLFW_APP_H
#define SOULSLIKEGL_GLFW_APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SceneRenderer.h"
#include "../../engine/Controller.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

namespace render {
    class App {
    public:
        static void start(int argc, char* argv[]);
    private:
        static void process_input();
        static void event_loop();
        static void set_mouse_position_callback();
        static void set_scroll_callback();
        static void set_framebuffer_size_callback();
        static void set_key_callback();
        static void glfw_create_window();
        static void set_scene();
        static void terminate();

        static SceneRenderer sceneRenderer;
        static engine::Controller controller;
        static GLFWwindow *window;
    };
}



#endif //SOULSLIKEGL_GLFW_APP_H
