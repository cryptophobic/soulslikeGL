//
// Created by dmitr on 11.09.2022.
//

#ifndef SOULSLIKEGL_CONTROLS_H
#define SOULSLIKEGL_CONTROLS_H

#include <map>

namespace world::controls {

    class Controls {
//        std::map<int, void *()> onKeyDownActionMethods {};
//        std::map<int, void *()> onKeyPressedActionMethods {};
//        std::map<int, void *()> onMouseButtonDownActionMethods {};
//        std::map<int, void *()> onMouseButtonPressedActionMethods {};
        void (*onMousePositionChanged) (double, double) = nullptr;
        void (*onMouseScroll) (double, double) = nullptr;
    };

} // controls

#endif //SOULSLIKEGL_CONTROLS_H
