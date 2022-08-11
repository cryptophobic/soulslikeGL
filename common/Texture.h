//
// Created by dima on 01.08.22.
//

#ifndef SOULSLIKEGL_TEXTURE_H
#define SOULSLIKEGL_TEXTURE_H

namespace common {

    class Texture {
    public:
        void set(const char *resourcePth, GLenum format = GL_RGB);
        // the texture ID
        unsigned int ID;
        int width;
        int height;
        int nrChannels;
    };

} // common

#endif //SOULSLIKEGL_TEXTURE_H
