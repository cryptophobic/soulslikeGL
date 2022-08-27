//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_WORLD_OBJECT_H
#define SOULSLIKEGL_WORLD_OBJECT_H

#include <vector>
#include <string>
#include <map>

namespace world {

    struct worldObjectVertices {
        std::vector<float> shape;
        std::string shapeId;
    };

    class Object {
    public:
        explicit Object(std::vector<float>);
        worldObjectVertices vertices;
        std::string vertexShaderPath;
        std::string fragmentShaderPath;
        std::string texturePath;
        bool dirty = true;
        enum ActionList : unsigned int {moveForward, moveBackward, rotateLeft, rotateRight};
        std::map<unsigned int, ActionList> getControlsMap();
        std::map<unsigned int, ActionList> actions;
    private:
    };

} // world

#endif //SOULSLIKEGL_WORLD_OBJECT_H
