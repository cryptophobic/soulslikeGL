#ifndef SOULSLIKEGL_CAMERA_H
#define SOULSLIKEGL_CAMERA_H

#include "Object.h"

namespace world {

    class Camera : public Object {
    public:
        explicit Camera(unsigned int newObjectId, ObjectState initialState);
        Object *objectToFollow = nullptr;
        void bindToTheObject(Object *object);
        void follow();
        float fov; // zoom
        void executeActions(float moveSpeed, float rotateSpeed);

    protected:
    };

} // world

#endif //SOULSLIKEGL_CAMERA_H
