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
#define SOULSLIKEGL_STRAFE_LEFT 16
#define SOULSLIKEGL_STRAFE_RIGHT 32

namespace world {

    class Object {
    public:
        Object();
        enum ActionList : unsigned int
                {moveForward = 1, moveBackward = 2, rotateLeft = 3, rotateRight = 4, strafeLeft = 5, strafeRight = 6, freeRotate = 7};

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
        float fov = 0.0f; // z axis
        virtual void updateDirection();
        ObjectGeometry* objectGeometry;
        glm::vec3 frontVector;
        glm::vec3 upVector{0.0f, 1.0f, 0.0f};

        bool display = true;
        std::map<int, ActionList> controls;
        unsigned int objectId;
    protected:
        unsigned int movingState = 0;
        std::map<unsigned int, void (Object::*)()> onKeyDownActionMethods {
        };
        std::map<unsigned int, void (Object::*)()> onKeyPressedActionMethods {
                {ActionList::moveForward, &Object::moveForwardMethod},
                {ActionList::moveBackward, &Object::moveBackwardMethod},
                {ActionList::rotateLeft, &Object::rotateLeftMethod},
                {ActionList::rotateRight, &Object::rotateRightMethod},
        };

        void strafeObject(float speed);
    };

} // world

#endif //SOULSLIKEGL_OBJECT_H
