#include "Camera.h"

#include "IGLSLShader.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>

void Camera::Init(int width, int height, float fov, float near = 0.01f, float far = 1000.0f)
{
    // Initializing camera
    this->_perspective = glm::perspective(glm::radians(fov), (float)width/(float)height, near, far);
    this->_position = glm::vec3(0.0f, 0.0f, -1.0f);
    this->_rotation = glm::vec3(0.0f);
};

void Camera::Update(IGLSLShader& program)
{
    // Initializing forward vector
    glm::vec3 forward = glm::vec3(
        cos(this->_rotation.y) * sin(-this->_rotation.x),
        sin(this->_rotation.y),
        cos(this->_rotation.y) * cos(-this->_rotation.x)
    );

    // Initializing right vector
    glm::vec3 right = glm::vec3(
        sin(-this->_rotation.x - glm::radians(90.0f)),
        0,
        cos(-this->_rotation.x - glm::radians(90.0f))
    );

    // Crossing forward and right vectors to initialize up vector
    glm::vec3 up = glm::cross(right, forward);

    // Initializing view using matrix multiplication
    glm::mat4 view =
        this->_perspective *
        glm::lookAt(
            glm::vec3(-this->_position.x, this->_position.y, this->_position.z),
            glm::vec3(-this->_position.x, this->_position.y, this->_position.z) + forward,
            up
        );

    // Sending view matrix to GPU
    program.UniformMatrix4fv("view", view);
}
