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
        texturePath = settings::rendering.textureDefaultPath;
    }
} // world