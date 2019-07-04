#include "Shaders.h"

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

void BasicGeoShader::Init()
{
    this->_programID = CreateShader(
        R"(
            #version 330 core

            layout(location = 0) in vec3 vertPosition;
            layout(location = 1) in vec4 vertColor;

            out vec3 fragPosition;
            out vec4 fragColor;

            uniform mat4 view;

            void main() {
                gl_Position = view * vec4(vertPosition, 1.0f);
                
                fragPosition = vertPosition;
                fragColor = vertColor;
            }
        )",
        R"(
            #version 330 core

            in vec3 fragPosition;
            in vec4 fragColor;

            out vec4 color;

            void main() {
                color = fragColor;
            }
        )"
    );

    // Generating VAO, VBO, and IBO
    if (this->_vaoID == 0)
        glGenVertexArrays(1, &this->_vaoID);
    if (this->_vboID == 0)
        glGenBuffers(1, &this->_vboID);
    if (this->_iboID == 0)
        glGenBuffers(1, &this->_iboID);

    // Binding the VAO and VBO, and IBO
    glBindVertexArray(this->_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_iboID);

    // Pointing the VAO to the correct location in the given GeoVertex3D object
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GeoVertex3D), (void*)offsetof(GeoVertex3D, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GeoVertex3D), (void*)offsetof(GeoVertex3D, color));

    // Unbinding the VAO
    glBindVertexArray(this->_vaoID);
}

void BasicGeoShader::End()
{
    // Binding the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->_vboID);

    // Uploading vertex data to the VBO
    glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(GeoVertex3D), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, this->_vertices.size() * sizeof(GeoVertex3D), this->_vertices.data());
    
    // Unbinding the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Binding the IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_iboID);

    // Uploading index data to the IBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->_indices.size() * sizeof(unsigned int), this->_indices.data());

    // Unbinding the IBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Clear vertex and index vectors
    this->_numIndices = this->_indices.size();
    this->_vertices.clear();
    this->_indices.clear();
}

void BasicGeoShader::Render()
{
    // Using GLSL program and binding the VAO
    this->Use();
    glBindVertexArray(this->_vaoID);

    // Drawing vertices
    glDrawElements(GL_TRIANGLES, this->_numIndices, GL_UNSIGNED_INT, 0);

    // Unbinding the GLSL program and unbinding the VAO
    glBindVertexArray(0);
    this->Unuse();
}

void BasicGeoShader::DrawTri(GeoVertex3D a, GeoVertex3D b, GeoVertex3D c)
{
    // Pushing vertices into vector
    this->_vertices.reserve(this->_vertices.size() + 3);
    this->_vertices.push_back(a);
    this->_vertices.push_back(b);
    this->_vertices.push_back(c);

    // Pushing corresponding indices into vector
    int firstIndex = this->_indices.size();
    this->_indices.reserve(this->_indices.size() + 3);
    this->_indices.push_back(firstIndex);
    this->_indices.push_back(firstIndex + 1);
    this->_indices.push_back(firstIndex + 2);
}