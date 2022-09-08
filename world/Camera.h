#ifndef SOULSLIKEGL_CAMERA_H
#define SOULSLIKEGL_CAMERA_H

#include "Object.h"

namespace world {

    class Camera : public Object {
    public:
        explicit Camera(unsigned int newObjectId, ObjectState initialState);
        Object *objectToFollow = nullptr;
        void followTheObject(Object *);
        void follow();
        float fov = 0.0f; // zoom
        float sensitivity;

    protected:
    };

} // world

#endif //SOULSLIKEGL_CAMERA_H
