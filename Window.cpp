#include "Window.h"

#include "Input.h"

void Window::Init(const std::string& name, int width, int height, unsigned int flags)
{
    // Not specifying a monitor
    GLFWmonitor* monitor = nullptr;

    // Setting the width and height of the window
    this->_width = width;
    this->_height = height;

    // Applying various window flags
    if (flags & WindowFlag::HIDDEN)
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    if (flags & WindowFlag::FULLSCREEN)
        monitor = glfwGetPrimaryMonitor();
    if (flags & WindowFlag::RESIZABLE)
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // Applying window hints
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

    // Creating the window
    this->_window = glfwCreateWindow(width, height, name.c_str(), monitor, nullptr);

    // Setting the current context to the new window
    glfwMakeContextCurrent(this->_window);

    // Creating an input manager using the new window
    this->_inputManager = new InputManager;
    this->_inputManager->Init(this->_window);
}

void Window::Destroy()
{
    // Garbage collecting window and input manager
    glfwDestroyWindow(this->_window);
    this->_inputManager->Destroy(this->_window);
}
