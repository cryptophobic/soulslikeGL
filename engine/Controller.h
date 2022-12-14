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
        void mouseMoveAction(double xPos, double yPos);
        void scrollCallback(double xOffset, double yOffset);
        void keyPressedAction(unsigned int);
        void keyDownAction(unsigned int);

        std::map<int /** keycode **/, unsigned int /** action **/> getControls();

        std::array<int, 4> getViewportVector(int width, int height);
        world::Scene *getCurrentScene();
    private:
        world::Scene *scene = nullptr;

    };

} // engine

#endif //SOULSLIKEGL_CONTROLLER_H
