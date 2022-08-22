//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_SCENERENDERER_H
#define SOULSLIKEGL_SCENERENDERER_H

#include <vector>
#include <map>
#include "../../world/Scene.h"
#include "common/Shader.h"
#include "common/Texture.h"

namespace render {

#define RENDER_VAO 0
#define RENDER_VBO 1

    struct renderObject {

    };

    class SceneRenderer {
    public:
        void set(world::Scene *);
        void draw();
    private:
        world::Scene *scene;
        std::map<std::string, unsigned int[2]> vertexBufferObjects; //VBOs{}, VAOs{};
        std::map<std::string, common::Shader*> shaderPrograms{};
        std::map<std::string, common::Texture*> textures{};
        void vertexBufferObjectInit(const world::worldObjectVertices& vertices);
    };

} // render

#endif //SOULSLIKEGL_SCENERENDERER_H
