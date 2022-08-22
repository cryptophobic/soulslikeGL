//
// Created by dima on 15.08.22.
//

#include "SceneRenderer.h"

namespace render {
    void SceneRenderer::set(world::Scene *newScene) {
        scene = newScene;
    }

    void SceneRenderer::draw() {
        for (auto worldObject : scene->objects) {
            vertexBufferObjectInit(worldObject->object->vertices);
        }
        // foreach (scene.objects)
        // if object is not initialized
        //
    }

    void SceneRenderer::vertexBufferObjectInit(const world::worldObjectVertices& vertices) {
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
    }
} // render