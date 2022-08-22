//
// Created by dima on 22.08.22.
//

#ifndef SOULSLIKEGL_WORLDCONFIG_H
#define SOULSLIKEGL_WORLDCONFIG_H

#include <glm/vec3.hpp>

namespace settings {
    const struct {
        const glm::vec3 objectPositions[10];
    } testWorld {
            .objectPositions = {
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
            }
    };
}

#endif //SOULSLIKEGL_WORLDCONFIG_H
