#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SceneRenderer.h"
#include "../../utils/filesystem_helper.h"

namespace render {
    void SceneRenderer::set(world::Scene *newScene) {
        scene = newScene;
    }

    void SceneRenderer::draw(glm::mat4 view, glm::mat4 projection) {
        viewMatrix = view;
        projectionMatrix = projection;
        for (auto object : scene->objects) {
            if (!object->display) continue;
            setRenderObject(object);
            renderRenderObject(object->objectId);
        }
    }

    std::string SceneRenderer::setVertexBufferObject(const world::Vertices& vertices) {
        if (!vertexBufferObjects.contains(vertices.shapeId)) {
            unsigned int VBO, VAO;

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (vertices.shape.size() * sizeof(GLfloat)), vertices.shape.data(), GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
            glEnableVertexAttribArray(0);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            vertexBufferObjects[vertices.shapeId][RENDER_VAO] = VAO;
            vertexBufferObjects[vertices.shapeId][RENDER_VBO] = VBO;
        }

        return vertices.shapeId;
    }

    std::string SceneRenderer::setShaders(world::ObjectGeometry *object) {
        // TODO: use some pairId for 2 shaders
        std::string pairId = object->texturePath + object->fragmentShaderPath;
        if (!shaderPrograms.contains(pairId)) {
            auto shaderProgram = new common::Shader();
            shaderProgram->set(
                    FileSystemHelper::getPath(object->vertexShaderPath).c_str(),
                    FileSystemHelper::getPath(object->fragmentShaderPath).c_str());
            shaderPrograms[pairId] = shaderProgram;
        }

        return pairId;
    }

    std::string SceneRenderer::setTextures(world::ObjectGeometry *object) {
        if (!textures.contains(object->texturePath)) {
            auto texture = new common::Texture();
            texture->set(FileSystemHelper::getPath(object->texturePath).c_str());
            textures[object->texturePath] = texture;
        }

        return object->texturePath;
    }

    unsigned int SceneRenderer::setRenderObject(world::Object *object) {
        if (object->objectGeometry->dirty || !renderObjects.contains(object->objectId)) {
            auto renderObject = new RenderObject();
            renderObject->vertexBufferObjectId = setVertexBufferObject(object->objectGeometry->vertices);
            renderObject->shaderProgramId = setShaders(object->objectGeometry);
            renderObject->textureId = setTextures(object->objectGeometry);
            renderObject->object = object;
            renderObjects[object->objectId] = renderObject;

            shaderPrograms[renderObject->shaderProgramId]->use();
            shaderPrograms[renderObject->shaderProgramId]->setInt("texture1", 0);

            //shaderProgram.setInt("texture2", 1);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, shaderPrograms[renderObject->shaderProgramId]->ID);
            //        glActiveTexture(GL_TEXTURE1);
            //        glBindTexture(GL_TEXTURE_2D, textureFace.ID);
            object->objectGeometry->dirty = false;
        }
        return object->objectId;
    }

    void SceneRenderer::renderRenderObject(unsigned int objectId) {

        std::string shaderProgramId = renderObjects[objectId]->shaderProgramId;

        bindVertexArray(renderObjects[objectId]->vertexBufferObjectId);
        useShaderProgram(shaderProgramId);

        auto object = renderObjects[objectId]->object;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, object->state.position);
        model = glm::rotate(model, glm::radians(object->state.pitch),glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(object->state.yaw),glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(object->state.roll),glm::vec3(0.0f, 0.0f, 1.0f));

        shaderPrograms[shaderProgramId]->setMat4("projection", projectionMatrix);
        shaderPrograms[shaderProgramId]->setMat4("view", viewMatrix);
        shaderPrograms[shaderProgramId]->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void SceneRenderer::bindVertexArray(const std::string& vertexBufferObjectId) {
        if (currentVAOActive != vertexBufferObjectId) {
            glBindVertexArray(vertexBufferObjects[vertexBufferObjectId][RENDER_VAO]);
            currentVAOActive = vertexBufferObjectId;
        }
    }

    void SceneRenderer::useShaderProgram(const std::string& shaderProgramId) {
        if (currentShaderActive != shaderProgramId) {
            shaderPrograms[shaderProgramId]->use();
            currentShaderActive = shaderProgramId;
        }
    }

} // render
