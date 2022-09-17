#ifndef SOULSLIKEGL_OBJECT_H
#define SOULSLIKEGL_OBJECT_H

namespace world::behaviours {
    class Move;
}

#include <glm/glm.hpp>
#include "ObjectGeometry.h"
#include "behaviours/Move.h"
#include "../settings/worldConfig.h"
#include "../settings/controls.h"

namespace world {

    class Object {
    public:
        explicit Object(unsigned int newObjectId, ObjectState initialState);

        void rotate();
        void move();
        virtual void executeActions();

        void keyPressedAction(settings::ActionList);
        void keyDownAction(settings::ActionList);
        void moveForwardMethod();
        void moveBackwardMethod();
        void rotateLeftMethod();
        void rotateRightMethod();
        void strafeLeftMethod();
        void strafeRightMethod();
        void freeRotateMethod(double, double, double, double);

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
        std::map<int, settings::ActionList> controls;
        unsigned int objectId;
        float sensitivity;
        behaviours::Move* behaviour;
    protected:
        unsigned int movingState = 0;
        double xOffset = 0;
        double yOffset = 0;

        float moveSpeed;
        float rotateSpeed;

        std::map<unsigned int, void (Object::*)()> onKeyDownActionMethods {
                {settings::ActionList::moveForward, &Object::moveForwardMethod},
                {settings::ActionList::moveBackward, &Object::moveBackwardMethod},
                {settings::ActionList::rotateLeft, &Object::rotateLeftMethod},
                {settings::ActionList::rotateRight, &Object::rotateRightMethod},
        };
        std::map<unsigned int, void (Object::*)()> onKeyPressedActionMethods {};

        void (Object::*onMouseMoveMethod) (double, double, double, double) = &Object::freeRotateMethod;
    };

} // world

#endif //SOULSLIKEGL_OBJECT_H
