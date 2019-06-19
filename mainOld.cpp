#include "GLSLProgram.h"
#include "Camera.h"
#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    //GLFWwindow* window;

    // Initializing GLFW
    if (!glfwInit())
        return -1;

    /*if (!window)
    {
        glfwTerminate();
        return -1;
    }*/

    Window window;
    window.Init("Test Window", 640, 480);

    // Initializing GLEW after creating valid GL context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    std::printf("%s\n", glGetString(GL_VERSION));

    // Initializing a vertex array object
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Initializing vertex positions
    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    // Initializing a buffer
    unsigned int buffer;
    glGenBuffers(1, &buffer); // Generate buffer

    // Select buffer for usage
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Size of positions (6 floats)
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    // Define position attribute for vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Initialize camera
    Camera camera(640, 480, 90.0f, 0.01f, 1000.0f);

    // Initialize the GLSL shader program
    GLSLProgram shader;
    shader.Init("res/shaders/basic.shader");

    // Main loop
    double timeInitial = glfwGetTime();
    while (!window.ShouldClose())
    {
        double timeFinal = glfwGetTime();
        float delta = timeFinal - timeInitial;
        timeInitial = glfwGetTime();

        if (window.GetKey(GLFW_KEY_UP) == GLFW_PRESS)
            camera.Rotate(0.0f, delta, 0.0f);
        if (window.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
            camera.Rotate(-delta, 0.0f, 0.0f);
        if (window.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
            camera.Rotate(delta, 0.0f, 0.0f);
        if (window.GetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
            camera.Rotate(0.0f, -delta, 0.0f);
        if (window.GetKey(GLFW_KEY_W) == GLFW_PRESS)
            camera.Translate(0.0f, 0.0f, delta);
        if (window.GetKey(GLFW_KEY_S) == GLFW_PRESS)
            camera.Translate(0.0f, 0.0f, -delta);
        if (window.GetKey(GLFW_KEY_A) == GLFW_PRESS)
            camera.Translate(-delta, 0.0f, 0.0f);
        if (window.GetKey(GLFW_KEY_D) == GLFW_PRESS)
            camera.Translate(delta, 0.0f, 0.0f);
        if (window.GetKey(GLFW_KEY_Q) == GLFW_PRESS)
            camera.Translate(0.0f, delta, 0.0f);
        if (window.GetKey(GLFW_KEY_E) == GLFW_PRESS)
            camera.Translate(0.0f, -delta, 0.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        camera.Update(shader);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.SwapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
