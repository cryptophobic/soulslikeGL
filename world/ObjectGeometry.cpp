//
// Created by dima on 15.08.22.
//

#include "ObjectGeometry.h"
#include "../settings/config.h"
#include <utility>

namespace world {
    ObjectGeometry::ObjectGeometry(std::vector<float> shape) {
        vertices.shape = std::move(shape);
        vertices.shapeId = "cube";
        // TODO: implement setting
        vertexShaderPath = settings::rendering.vertexShaderDefaultPAth;
        fragmentShaderPath = settings::rendering.fragmentShaderDefaultPAth;
        texturePath = settings::rendering.textureDefaultPaths[0];
        //texturePaths.emplace_back(settings::rendering.textureDefaultPaths[1]);
    }
} // world
