#include <glad/glad.h>
#include <iostream>
#include "Texture.h"
#include "../images/stb_image.h"

namespace common {
    Texture::Texture(const char *resourcePth, GLenum format) {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        unsigned char *data = stbi_load(resourcePth, &width, &height,&nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        stbi_set_flip_vertically_on_load(true);
    }
} // common