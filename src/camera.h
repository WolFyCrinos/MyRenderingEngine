//
// Created by FrançoisMARTEEL on 6/1/2024.
//

#ifndef MYRENDERINGENGINE_CAMERA_H
#define MYRENDERINGENGINE_CAMERA_H

#endif //MYRENDERINGENGINE_CAMERA_H

#include <vk_types.h>
#include <SDL2/SDL_events.h>

class Camera {
public:
    glm::vec3 velocity;
    glm::vec3 position;
    // vertical rotation
    float pitch { 0.f };
    // horizontal rotation
    float yaw { 0.f };

    glm::mat4 getViewMatrix();
    glm::mat4 getRotationMatrix();

    void processSDLEvent(SDL_Event& e);

    void update();
};