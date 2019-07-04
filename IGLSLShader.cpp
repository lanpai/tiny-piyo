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

void IGLSLShader::UniformMatrix4fv(const std::string& name, glm::mat4& matrix)
{
    // Uploading mat4 data to the uniform
    this->Use();
    unsigned int id = this->GetUniformLocation(name);
    glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0]);
}