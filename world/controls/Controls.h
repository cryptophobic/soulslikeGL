#ifndef SOULSLIKEGL_CONTROLS_H
#define SOULSLIKEGL_CONTROLS_H

#include <map>
#include <functional>

namespace world::controls {

    class Controls {
        std::map<int, std::function<void()>> onKeyDownActionMethods {};
        std::map<int, std::function<void()>> onKeyPressedActionMethods {};
        std::map<int, std::function<void()>> onMouseButtonDownActionMethods {};
        std::map<int, std::function<void()>> onMouseButtonPressedActionMethods {};
        std::function<void(double, double)> onMousePositionChanged = nullptr;
        std::function<void(double, double)> onMouseScroll = nullptr;
    };

} // controls

#endif //SOULSLIKEGL_CONTROLS_H
