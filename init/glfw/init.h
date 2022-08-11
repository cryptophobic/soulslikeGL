//
// Created by dima on 11.08.22.
//

#ifndef SOULSLIKEGL_GLFW_INIT_H
#define SOULSLIKEGL_GLFW_INIT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../common/Texture.h"
#include "../../common/Shader.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

namespace init {
    class Init {
    public:
        static void start(int argc, char* argv[]);
        static void terminate();
        static void set_mouse_position_callback();
        static void set_scroll_callback();
        static void set_framebuffer_size_callback();
        static void set_viewport_size(int x, int y, int width, int height);
        static void process_input();
        static GLFWwindow *get_window();
        static void load_VAO_VBO();
        static void enable_gl_depth_test();
        static void event_loop(common::Texture, common::Texture ,common::Shader);
    private:
        static void glfw_create_window();
        static void glad_init();
    };
}



#endif //SOULSLIKEGL_GLFW_INIT_H
