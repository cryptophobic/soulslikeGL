//
// Created by dima on 14.08.22.
//

#ifndef SOULSLIKEGL_CONFIG_H
#define SOULSLIKEGL_CONFIG_H

namespace settings {
    const struct {
        const struct {
            int width;
            int height;
        } resolution = { .width = 800, .height = 600};
    } screen;

    const struct {
        const char *title;
    } window { .title = "Murka Window" };

    const struct {
        const char *vertexShaderDefaultPAth;
        const char *fragmentShaderDefaultPAth;
        const char *fragmentShaderSelectedPAth;
        const char *textureDefaultPaths[2];
    } rendering {
        .vertexShaderDefaultPAth = "shaders/shader.vert",
        .fragmentShaderDefaultPAth = "shaders/shader.frag",
        .fragmentShaderSelectedPAth = "shaders/shaderSelected.frag",
        .textureDefaultPaths = {"textures/container.jpg", "textures/awesomeface.png"}
    };
}

#endif //SOULSLIKEGL_CONFIG_H
