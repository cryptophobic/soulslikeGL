//
// Created by dima on 15.08.22.
//

#include "Object.h"
#include "../settings/config.h"
#include "../settings/worldConfig.h"
#include <utility>

namespace world {
    Object::Object(std::vector<float> shape) {
        vertices.shape = std::move(shape);
        vertices.shapeId = "cube";
        // TODO: implement setting
        vertexShaderPath = settings::rendering.vertexShaderDefaultPAth;
        fragmentShaderPath = settings::rendering.fragmentShaderDefaultPAth;
        texturePath = settings::rendering.textureDefaultPaths[0];
        controls = settings::objectInputSettings;
        //texturePaths.emplace_back(settings::rendering.textureDefaultPaths[1]);
    }

    void Object::onKeyDownAction(ActionList action) {
        if (onKeyDownActionMethods.contains(action)) {
            ((*this).*(onKeyDownActionMethods[action]))();
        }
    }

    void Object::onKeyPressedAction(ActionList action) {
        if (onKeyPressedActionMethods.contains(action)) {
            ((*this).*(onKeyPressedActionMethods[action]))();
        }
    }

    void Object::moveForwardMethod() {
        movingState |= SOULSLIKEGL_MOVE_FORWARD;
    }

    void Object::moveBackwardMethod() {
        movingState |= SOULSLIKEGL_MOVE_BACKWARD;
    }

    void Object::rotateLeftMethod() {
        movingState |= SOULSLIKEGL_ROTATE_LEFT;
    }

    void Object::rotateRightMethod() {
        movingState |= SOULSLIKEGL_ROTATE_RIGHT;
    }

    unsigned int Object::getMovingState() const {
        return movingState;
    }

    void Object::stopMoving(unsigned int moving) {
        movingState ^= moving;
    }
} // world
