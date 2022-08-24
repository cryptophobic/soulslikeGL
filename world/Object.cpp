//
// Created by dima on 15.08.22.
//

#include "Object.h"
#include "../settings/config.h"
#include <utility>

namespace world {
    Object::Object(std::vector<float> shape) {
        vertices.shape = std::move(shape);
        vertices.shapeId = "cube";
        // TODO: implement setting
        vertexShaderPath = settings::rendering.vertexShaderDefaultPAth;
        fragmentShaderPath = settings::rendering.fragmentShaderDefaultPAth;
        texturePath = settings::rendering.textureDefaultPaths[0];
        //texturePaths.emplace_back(settings::rendering.textureDefaultPaths[1]);
    }

    void Object::moveForward() {
        actions.push(OBJECT_MOVE_FORWARD);
    }

    void Object::moveBackward() {
        actions.push(OBJECT_MOVE_BACKWARD);
    }

    void Object::rotateLeft() {
        actions.push(OBJECT_ROTATE_LEFT);
    }

    void Object::rotateRight() {
        actions.push(OBJECT_ROTATE_RIGHT);
    }
} // world