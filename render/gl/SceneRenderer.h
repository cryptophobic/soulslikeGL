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

    struct renderObject {

    };

    class SceneRenderer {
    public:
        void setScene(world::Scene);
        void drawScene();
    private:
        world::Scene scene;
        std::map<std::string, int> VBOs{}, VAOs{};
        std::map<std::string, common::Shader*> shaderPrograms{};
        std::map<std::string, common::Texture*> textures{};
        //std::vector<unsigned int> VBOs{}, VAOs{};
        //std::vector<common::Shader *> shaderPrograms{};
        //std::vector<common::Texture> textures{};

    };

} // render

#endif //SOULSLIKEGL_SCENERENDERER_H
