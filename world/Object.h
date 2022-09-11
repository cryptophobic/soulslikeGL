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

    struct ObjectState {
        float yaw;
        float pitch;
        float roll;
        glm::vec3 position;
    };

    class Object {
    public:
        explicit Object(unsigned int newObjectId, ObjectState initialState);
        enum Directions : int {
            forward = 1, backward = -1,
            left = 1, right = -1
        };

        enum ActionList : unsigned int {
            moveForward = 1, moveBackward = 2,
            rotateLeft = 3, rotateRight = 4,
            strafeLeft = 5, strafeRight = 6,
            freeRotate = 7, zoom = 8
        };

        void rotateObject(int direction);
        void moveObject(int direction);
        void strafeObject(int direction);
        void rotate();
        void move();
        virtual void executeActions();

        void keyPressedAction(ActionList);
        void keyDownAction(ActionList);
        void moveForwardMethod();
        void moveBackwardMethod();
        void rotateLeftMethod();
        void rotateRightMethod();
        void strafeLeftMethod();
        void strafeRightMethod();
        void freeRotateMethod(double, double, double, double);

        [[nodiscard]] unsigned int getMovingState() const;
        void stopMoving(unsigned int moving);

        ObjectState state {
            0.0f,
            0.0f,
            0.0f,
            {0.0f, 0.0f, 0.0f}
        };

        void updateDirection();
        ObjectGeometry* objectGeometry = nullptr;
        glm::vec3 frontVector{0.0f, 0.0f, 0.0f};
        glm::vec3 upVector{0.0f, 1.0f, 0.0f};

        bool display = true;
        std::map<int, ActionList> controls;
        unsigned int objectId;
        float sensitivity;
    protected:
        unsigned int movingState = 0;
        double xOffset = 0;
        double yOffset = 0;

        float moveSpeed;
        float rotateSpeed;

        std::map<unsigned int, void (Object::*)()> onKeyDownActionMethods {
                {ActionList::moveForward, &Object::moveForwardMethod},
                {ActionList::moveBackward, &Object::moveBackwardMethod},
                {ActionList::rotateLeft, &Object::rotateLeftMethod},
                {ActionList::rotateRight, &Object::rotateRightMethod},
        };
        std::map<unsigned int, void (Object::*)()> onKeyPressedActionMethods {};

        void (Object::*onMouseMoveMethod) (double, double, double, double) = &Object::freeRotateMethod;

//        std::map<unsigned int, void (Object::*)()> onMouseEventsMethods {
//                {ActionList::freeRotate, &Object::freeRotateMethod},
//                {ActionList::zoom, &Object::zoomMethod},
//        };
    };

} // world

#endif //SOULSLIKEGL_OBJECT_H
