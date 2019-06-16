#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm/mat4x4.hpp>

class Camera
{
    public:
        Camera(int width, int height, float fov, float near, float far);

        void Update(unsigned int programID);

        void SetX(float x) { this->_position.x = -1.0f * x; }
        void SetY(float y) { this->_position.y = -1.0f * y; }

        void Translate(float x, float y, float z) {this->_position += glm::vec3(x, y, z); };
        void Rotate(float x, float y, float z) { this->_rotation += glm::vec3(x, y, z); };
    private:
        glm::mat4 _perspective;
        glm::vec3 _position;
        glm::vec3 _rotation;
};

#endif
