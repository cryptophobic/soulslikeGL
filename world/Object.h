//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_WORLD_OBJECT_H
#define SOULSLIKEGL_WORLD_OBJECT_H

#include <vector>
#include <string>
#include <map>

#define SOULSLIKEGL_MOVE_FORWARD 1
#define SOULSLIKEGL_MOVE_BACKWARD 2
#define SOULSLIKEGL_ROTATE_LEFT 4
#define SOULSLIKEGL_ROTATE_RIGHT 8

namespace world {

    struct worldObjectVertices {
        std::vector<float> shape;
        std::string shapeId;
    };

    class Object {
    public:
        enum ActionList : unsigned int {moveForward, moveBackward, rotateLeft, rotateRight};
        explicit Object(std::vector<float>);
        void onKeyDownAction(ActionList);
        void onKeyPressedAction(ActionList);
        void moveForwardMethod();
        void moveBackwardMethod();
        void rotateLeftMethod();
        void rotateRightMethod();
        unsigned int getMovingState() const;
        void stopMoving(unsigned int moving);
        worldObjectVertices vertices;
        std::string vertexShaderPath;
        std::string fragmentShaderPath;
        std::string texturePath;
        bool dirty = true;
        std::map<int, ActionList> controls;
    private:
        unsigned int movingState = 0;
        std::map<unsigned int, void (Object::*)()> onKeyDownActionMethods {
        };
        std::map<unsigned int, void (Object::*)()> onKeyPressedActionMethods {
                {ActionList::moveForward, &Object::moveForwardMethod},
                {ActionList::moveBackward, &Object::moveBackwardMethod},
                {ActionList::rotateLeft, &Object::rotateLeftMethod},
                {ActionList::rotateRight, &Object::rotateRightMethod},
        };
    };

} // world

#endif //SOULSLIKEGL_WORLD_OBJECT_H
