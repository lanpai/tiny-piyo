#ifndef _TINY_PIYO_GLSLPROGRAM_H
#define _TINY_PIYO_GLSLPROGRAM_H

#include "GL/glew.h"

#include <glm/gtc/matrix_transform.hpp>

#include <string>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

enum class ShaderType
{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
};

ShaderProgramSource ParseShader(const std::string& filepath);
unsigned int CompileShader(unsigned int type, const std::string& source);
unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

class IGLSLShader
{
    public:
        ~IGLSLShader();

        void Use() { glUseProgram(this->_programID); };
        void Unuse() { glUseProgram(0); };

        unsigned int GetUniformLocation(const std::string& name);

        void UniformMatrix4fv(const std::string& name, glm::mat4& value);
        void UniformBool(const std::string& name, bool value);
        void UniformInt(const std::string& name, int value);
        void UniformFloat(const std::string& name, float value);

    protected:
        unsigned int _programID;
};

#endif
