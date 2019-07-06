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

    // Creating the window
    this->_window = glfwCreateWindow(width, height, name.c_str(), monitor, nullptr);

    // Setting the current context to the new window
    glfwMakeContextCurrent(this->_window);

    // Creating an input manager using the new window
    this->_inputManager = new InputManager;
    this->_inputManager->Init(this);
}

void Window::Destroy()
{
    // Garbage collecting window and input manager
    this->_inputManager->Destroy();
    glfwDestroyWindow(this->_window);
}
