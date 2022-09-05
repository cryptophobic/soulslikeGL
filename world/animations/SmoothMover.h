//
// Created by dmitr on 05.09.2022.
//

#ifndef SOULSLIKEGL_SMOOTHMOVER_H
#define SOULSLIKEGL_SMOOTHMOVER_H

#include <glm/vec3.hpp>

namespace world {

    class SmoothMover {
    public:
        void setFinalDestination(glm::vec3 position, float pitch, float yaw, float roll);
        void setTimeout(int milliseconds);
        void animate();
    private:
    };

} // world

#endif //SOULSLIKEGL_SMOOTHMOVER_H
