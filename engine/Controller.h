//
// Created by dima on 11.08.22.
//

#ifndef SOULSLIKEGL_CONTROLLER_H
#define SOULSLIKEGL_CONTROLLER_H

#include <array>
#include "../world/Scene.h"

namespace engine {

    class Controller {
    public:
        void mousePositionCallback(double xPos, double yPos);
        void scrollCallback(double xOffset, double yOffset);
        void action(unsigned int);

        std::map<int /** keycode **/, unsigned int /** action **/> getControls();

        std::array<int, 4> getViewportVector(int width, int height);
        world::Scene *getCurrentScene();

        double lastX = 400, lastY = 300;
        bool firstMouse = true;
    private:
        world::Scene *scene = nullptr;

    };

} // engine

#endif //SOULSLIKEGL_CONTROLLER_H
