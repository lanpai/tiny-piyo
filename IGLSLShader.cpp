#include "IGLSLShader.h"

#include <fstream>
#include <sstream>

ShaderProgramSource ParseShader(const std::string& filepath)
{
    // Initializing input file stream
    std::ifstream stream(filepath.c_str());
    if (!stream)
        std::printf("Failed to open shader file \"%s\"\n", filepath.c_str());

    // Parsing each line from file stream
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        // Checking for #shader keyword
        if (line.find("#shader") != std::string::npos)
        {
            // Checking shader type
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            // Writing line to associated string stream
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int CompileShader(unsigned int type, const std::string& source)
{
    // Initializing OpenGL shader
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Compiling shader and error checking
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::printf(
            "Failed to compile %s shader!\n%s\n",
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment"),
            message
        );
        glDeleteShader(id);
        return 0;
    }

    #if PIYO_VERBOSITY >= 3
    std::printf(
        "%s shader initialized as #%d\n",
        (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"),
        id
    );
    #endif

    return id;
}

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // Initializing OpenGL shader program
    unsigned int program = glCreateProgram();

    // Compiling vertex and fragment shaders
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // Linking shaders into OpenGL program
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // Cleaning up shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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