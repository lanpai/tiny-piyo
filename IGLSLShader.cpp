#include "IGLSLShader.h"

IGLSLShader::~IGLSLShader()
{
    glDeleteProgram(this->_programID);
}

unsigned int IGLSLShader::GetUniformLocation(const std::string& name)
{
    this->Use();
    return glGetUniformLocation(this->_programID, name.c_str());
}

void IGLSLShader::UniformMatrix4fv(const std::string& name, glm::mat4& matrix)
{
    this->Use();
    unsigned int id = this->GetUniformLocation(name);
    glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0]);
}