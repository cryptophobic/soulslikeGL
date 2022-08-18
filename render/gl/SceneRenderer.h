//
// Created by dima on 15.08.22.
//

#ifndef SOULSLIKEGL_SCENERENDERER_H
#define SOULSLIKEGL_SCENERENDERER_H

#include <vector>
#include "../../world/Scene.h"
#include "common/Shader.h"
#include "common/Texture.h"

namespace render {

    struct renderObject {

    };

    class SceneRenderer {
    public:
        void setScene(world::Scene scene);
        void drawScene();
    private:
        world::Scene scene;
        std::vector<unsigned int> VBOs{}, VAOs{};
        std::vector<common::Shader *> shaderPrograms{};
        std::vector<common::Texture> textures{};

    };

} // render

#endif //SOULSLIKEGL_SCENERENDERER_H
