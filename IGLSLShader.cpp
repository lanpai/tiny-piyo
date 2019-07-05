#include "IGLSLShader.h"

IGLSLShader::~IGLSLShader()
{
    // Garbage collecting the GLSL program
    glDeleteProgram(this->_programID);
}

unsigned int IGLSLShader::GetUniformLocation(const std::string& name)
{
    // Returning the location of the given uniform
    this->Use();
    return glGetUniformLocation(this->_programID, name.c_str());
}

void IGLSLShader::UniformMatrix4fv(const std::string& name, glm::mat4& value)
{
    // Uploading mat4 data to the uniform
    this->Use();
    unsigned int id = this->GetUniformLocation(name);
    glUniformMatrix4fv(id, 1, GL_FALSE, &value[0][0]);
}

void IGLSLShader::UniformBool(const std::string& name, bool value)
{
    // Uploading boolean data to the uniform
    this->Use();
    unsigned int id = this->GetUniformLocation(name);
    glUniform1i(id, value);
}

void IGLSLShader::UniformInt(const std::string& name, int value)
{
    // Uploading integer data to the uniform
    this->Use();
    unsigned int id = this->GetUniformLocation(name);
    glUniform1i(id, value);
}

void IGLSLShader::UniformFloat(const std::string& name, float value)
{
    // Uploading integer data to the uniform
    this->Use();
    unsigned int id = this->GetUniformLocation(name);
    glUniform1f(id, value);
}