//
// Created by dima on 27.08.22.
//

#ifndef SOULSLIKEGL_OBJECT_H
#define SOULSLIKEGL_OBJECT_H

#include <glm/glm.hpp>
#include "ObjectGeometry.h"

#define SOULSLIKEGL_MOVE_FORWARD 1
#define SOULSLIKEGL_MOVE_BACKWARD 2
#define SOULSLIKEGL_ROTATE_LEFT 4
#define SOULSLIKEGL_ROTATE_RIGHT 8

namespace world {

    class Object {
    public:
        Object();
        enum ActionList : unsigned int
                {moveForward, moveBackward, rotateLeft, rotateRight, strafeLeft, strafeRight, freeRotate};

        void rotateObject(float objectSpeed);
        void moveObject(float objectSpeed);
        void move(float moveSpeed, float rotateSpeed);

        void onKeyDownAction(ActionList);
        void onKeyPressedAction(ActionList);
        void moveForwardMethod();
        void moveBackwardMethod();
        void rotateLeftMethod();
        void rotateRightMethod();
        void strafeLeftMethod();
        void strafeRightMethod();

        [[nodiscard]] unsigned int getMovingState() const;
        void stopMoving(unsigned int moving);


        glm::vec3 position;
        float pitch = 0.0f; // x axis
        float yaw = 0.0f;// y axis
        float fow = 0.0f; // z axis
        ObjectGeometry* objectGeometry;
        glm::vec3 direction;

        bool display = true;
        std::map<int, ActionList> controls;
        unsigned int objectId;
    private:
        void updateDirection();
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

#endif //SOULSLIKEGL_OBJECT_H
