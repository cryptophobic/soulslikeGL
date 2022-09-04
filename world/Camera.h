#ifndef SOULSLIKEGL_CAMERA_H
#define SOULSLIKEGL_CAMERA_H

#include "Object.h"

namespace world {

    class Camera : public Object {
    public:
        Camera();
        Object *objectToFollow;
        void followTheObject(Object *);
        void follow();

    protected:
        const float sensitivity;
    };

} // world

#endif //SOULSLIKEGL_CAMERA_H
