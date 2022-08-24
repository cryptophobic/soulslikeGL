//
// Created by dima on 15.08.22.
//

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
        for (auto worldObject : scene->objects) {
            setRenderObject(worldObject);
            renderRenderObject(worldObject->objectId);
        }
    }

    std::string SceneRenderer::setVertexBufferObject(const world::worldObjectVertices& vertices) {
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
            vertexBufferObjects[vertices.shapeId][RENDER_VBO] = VAO;
        }

        return vertices.shapeId;
    }

    std::string SceneRenderer::setShaders(world::Object *object) {
        // TODO: use some pairId for 2 shaders
        std::string pairId = object->texturePath + object->fragmentShaderPath;
        if (!shaderPrograms.contains(pairId)) {
            auto shaderProgram = new common::Shader();
            shaderProgram->set(
                    FileSystem::getPath(object->vertexShaderPath).c_str(),
                    FileSystem::getPath(object->fragmentShaderPath).c_str());
            shaderPrograms[pairId] = shaderProgram;
        }

        return pairId;
    }

    std::string SceneRenderer::setTextures(world::Object *object) {
        if (!textures.contains(object->texturePath)) {
            auto texture = new common::Texture();
            texture->set(FileSystem::getPath(object->texturePath).c_str());
            textures[object->texturePath] = texture;
        }

        return object->texturePath;
    }

    unsigned int SceneRenderer::setRenderObject(world::WorldObject *worldObject) {
        if (!renderObjects.contains(worldObject->objectId)) {
            auto renderObject = new RenderObject();
            renderObject->vertexBufferObjectId = setVertexBufferObject(worldObject->object->vertices);
            renderObject->shaderProgramId = setShaders(worldObject->object);
            renderObject->textureId = setTextures(worldObject->object);
            renderObject->worldObject = worldObject;
            renderObjects[worldObject->objectId] = renderObject;

            shaderPrograms[renderObject->shaderProgramId]->use();
            shaderPrograms[renderObject->shaderProgramId]->setInt("texture1", 0);

            //shaderProgram.setInt("texture2", 1);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, shaderPrograms[renderObject->shaderProgramId]->ID);
            //        glActiveTexture(GL_TEXTURE1);
            //        glBindTexture(GL_TEXTURE_2D, textureFace.ID);

        }
    }

    void SceneRenderer::renderRenderObject(unsigned int objectId) {

        std::string vertexBufferObjectId = renderObjects[objectId]->vertexBufferObjectId;
        std::string shaderProgramId = renderObjects[objectId]->shaderProgramId;

        //TODO: don't need to bind it every time if it had been bound previous time.
        glBindVertexArray(vertexBufferObjects[vertexBufferObjectId][RENDER_VAO]);
        shaderPrograms[shaderProgramId]->use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, renderObjects[objectId]->worldObject->position);//cubePositions[i]);
//        float angle = 20.0f * i;
//        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f + angle),glm::vec3(0.0f, 0.0f, 1.0f));
//        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f + angle * 2),glm::vec3(0.0f, 1.0f, 0.0f));
//        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f + angle * 3),glm::vec3(1.0f, 0.0f, 0.0f));

        shaderPrograms[shaderProgramId]->setMat4("projection", projectionMatrix);
        shaderPrograms[shaderProgramId]->setMat4("view", viewMatrix);
        shaderPrograms[shaderProgramId]->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
} // render