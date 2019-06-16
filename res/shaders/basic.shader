#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
uniform mat4 view;

void main()
{
    gl_Position = vec4(position, 1.0f);
    gl_Position = view * gl_Position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(1.0, 0.0, 0.0, 1.0);
};
