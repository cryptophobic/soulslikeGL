//
// Created by dima on 27.08.22.
//

#include <iostream>
#include "WorldObject.h"

namespace world {
    WorldObject::WorldObject() {
        updateDirection();
    }

    void WorldObject::rotateObject(float objectSpeed) {
        yaw += objectSpeed*50;
        std::cout << "yaw object" << yaw << std::endl;

        updateDirection();
    }

    void WorldObject::updateDirection() {
        direction.x = (float) cos((glm::radians(-yaw)) * cos(glm::radians(pitch)));
        direction.y = (float) sin(glm::radians(pitch));
        direction.z = (float) (sin(glm::radians(-yaw)) * cos(glm::radians(pitch)));

//        std::cout << direction.x << " " << direction.y << " " << direction.z << std::endl;

        //        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f + angle),glm::vec3(0.0f, 0.0f, 1.0f));
//        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f + angle * 2),glm::vec3(0.0f, 1.0f, 0.0f));
//        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f + angle * 3),glm::vec3(1.0f, 0.0f, 0.0f));


        direction = glm::normalize(direction);
//        std::cout << direction.x << " " << direction.y << " " << direction.z << std::endl;
    }


} // world