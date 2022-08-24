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

    struct RenderObject {
        world::WorldObject *worldObject;
        std::string vertexBufferObjectId;
        std::string shaderProgramId;
        std::string textureId;
    };

    class SceneRenderer {
    public:
        void set(world::Scene *);
        void draw(glm::mat4 view, glm::mat4 projection);
    private:
        world::Scene *scene;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        std::map<unsigned int, RenderObject*> renderObjects;
        std::map<std::string, unsigned int[2]> vertexBufferObjects;
        std::map<std::string, common::Shader *> shaderPrograms{};
        std::map<std::string, common::Texture *> textures{};
        std::string setVertexBufferObject(const world::worldObjectVertices &vertices);
        std::string setShaders(world::Object *);
        std::string setTextures(world::Object *);
        unsigned int setRenderObject(world::WorldObject *);
        void renderRenderObject(unsigned int objectId);
        void bindVertexArray(const std::string&);
        void useShaderProgram(const std::string&);
        std::string currentShaderActive;
        std::string currentVAOActive;


    };

} // render

#endif //SOULSLIKEGL_SCENERENDERER_H
