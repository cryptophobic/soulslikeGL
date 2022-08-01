//
// Created by dima on 01.08.22.
//

#ifndef SOULSLIKEGL_TEXTURE_H
#define SOULSLIKEGL_TEXTURE_H

namespace common {

    class Texture {
    public:
        Texture(const char *resourcePth);
        // the texture ID
        unsigned int ID;
        int width;
        int height;
        int nrChannels;
    };

} // common

#endif //SOULSLIKEGL_TEXTURE_H
