//
// Created by dima on 07.08.22.
//

#ifndef SOULSLIKEGL_SQUARE_H
#define SOULSLIKEGL_SQUARE_H

namespace objects {
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    const float square_vertices[] = {
            // positions          // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
    };

    const unsigned int square_indices[] = { // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
}

#endif //SOULSLIKEGL_SQUARE_H
