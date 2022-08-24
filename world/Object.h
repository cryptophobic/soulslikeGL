//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_WORLD_OBJECT_H
#define SOULSLIKEGL_WORLD_OBJECT_H

#include <vector>
#include <string>
#include <stack>

#define OBJECT_MOVE_FORWARD 1
#define OBJECT_MOVE_BACKWARD 2
#define OBJECT_ROTATE_LEFT 4
#define OBJECT_ROTATE_RIGHT 8


namespace world {

    struct worldObjectVertices {
        std::vector<float> shape;
        std::string shapeId;
    };

    class Object {
    public:
        Object(std::vector<float>);
        void moveForward();
        void moveBackward();
        void rotateLeft();
        void rotateRight();
        worldObjectVertices vertices;
        std::string vertexShaderPath;
        std::string fragmentShaderPath;
        std::string texturePath;
        bool dirty = true;

    private:
        std::stack<unsigned int> actions;
    };

} // world

#endif //SOULSLIKEGL_WORLD_OBJECT_H
