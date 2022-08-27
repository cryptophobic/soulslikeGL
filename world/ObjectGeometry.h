//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_WORLD_OBJECT_H
#define SOULSLIKEGL_WORLD_OBJECT_H

#include <vector>
#include <string>
#include <map>

namespace world {

    struct Vertices {
        std::vector<float> shape;
        std::string shapeId;
    };

    class ObjectGeometry {
    public:
        explicit ObjectGeometry(std::vector<float>);
        Vertices vertices;
        std::string vertexShaderPath;
        std::string fragmentShaderPath;
        std::string texturePath;
        bool dirty = true;
    private:
    };

} // world

#endif //SOULSLIKEGL_WORLD_OBJECT_H
