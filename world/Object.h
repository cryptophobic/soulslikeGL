//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_WORLD_OBJECT_H
#define SOULSLIKEGL_WORLD_OBJECT_H

#include <vector>
#include <string>

namespace world {

    class Object {
    public:
        Object(std::vector<float>);
        std::vector<float> shape;
        std::string vertexShaderPath;
        std::string fragmentShaderPath;
        std::string texturePath;
    };

} // world

#endif //SOULSLIKEGL_WORLD_OBJECT_H
