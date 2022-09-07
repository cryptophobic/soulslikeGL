#ifndef SOULSLIKEGL_CAMERA_H
#define SOULSLIKEGL_CAMERA_H

#include "Object.h"

namespace world {

    struct CameraStateStruct : ObjectStateStruct {
        float fov;
        float sensitivity;
    };

    class Camera : public Object {
    public:
        explicit Camera(CameraStateStruct initialState);
        Object *objectToFollow = nullptr;
        CameraStateStruct state;
        void bindObjectToFollow(Object *);
        void follow();
    };

} // world

#endif //SOULSLIKEGL_CAMERA_H
