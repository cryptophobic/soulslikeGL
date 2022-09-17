#ifndef SOULSLIKEGL_OBJECTV2_H
#define SOULSLIKEGL_OBJECTV2_H

#include <glm/glm.hpp>
#include "ObjectGeometry.h"
#include "../settings/worldConfig.h"

namespace world {

    class ObjectV2 {
    public:
        explicit ObjectV2(unsigned int newObjectId, ObjectState initialState);

        enum ActionList : unsigned int {
            moveForward = 1, moveBackward = 2,
            rotateLeft = 3, rotateRight = 4,
            strafeLeft = 5, strafeRight = 6,
            freeRotate = 7, zoom = 8
        };

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

        ObjectState state{
                0.0f,
                0.0f,
                0.0f,
                {0.0f, 0.0f, 0.0f}
        };

        void updateDirection();

        ObjectGeometry *objectGeometry = nullptr;
        glm::vec3 frontVector{0.0f, 0.0f, 0.0f};
        glm::vec3 upVector{0.0f, 1.0f, 0.0f};

        bool display = true;
        std::map<int, ActionList> controls;
        unsigned int objectId;
        float sensitivity;
    protected:
        double xOffset = 0;
        double yOffset = 0;

        std::map<unsigned int, void (ObjectV2::*)()> onKeyDownActionMethods{
                {ActionList::moveForward,  &ObjectV2::moveForwardMethod},
                {ActionList::moveBackward, &ObjectV2::moveBackwardMethod},
                {ActionList::rotateLeft,   &ObjectV2::rotateLeftMethod},
                {ActionList::rotateRight,  &ObjectV2::rotateRightMethod},
        };
        std::map<unsigned int, void (ObjectV2::*)()> onKeyPressedActionMethods{};

        void (ObjectV2::*onMouseMoveMethod)(double, double, double, double) = &ObjectV2::freeRotateMethod;
    };

} // world

#endif //SOULSLIKEGL_OBJECTV2_H
