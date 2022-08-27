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
        actions = settings::objectInputSettings;
        //texturePaths.emplace_back(settings::rendering.textureDefaultPaths[1]);
    }

    std::map<unsigned int, Object::ActionList> Object::getControlsMap() {
        return actions;
    }
} // world