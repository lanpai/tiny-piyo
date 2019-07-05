#ifndef _TINY_PIYO_CAMERA_H
#define _TINY_PIYO_CAMERA_H

#include <glm/mat4x4.hpp>

class IGLSLShader;

class Camera
{
    public:
        void Init(int width, int height, float fov, float near, float far);

        void Update(IGLSLShader& program);

        void SetPosX(float x) { this->_position.x = -x; }
        void SetPosY(float y) { this->_position.y = -y; }
        void SetPosZ(float z) { this->_position.z = -z; }

        const glm::vec3& GetRotation() { return this->_rotation; }
        const glm::vec3& GetPosition() { return this->_position; }

        void SetRotation(float x, float y, float z) { this->_rotation = glm::vec3(x, y, z); }
        void SetPosition(float x, float y, float z) { this->_position = glm::vec3(-x, -y, -z); }

        void Translate(float x, float y, float z) {this->_position += glm::vec3(x, y, z); };
        void Rotate(float x, float y, float z) { this->_rotation += glm::vec3(x, y, z); };
    private:
        glm::mat4 _perspective;
        glm::vec3 _position;
        glm::vec3 _rotation;
};

#endif
