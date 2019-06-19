#include "Window.h"

void Window::Init(const std::string& name, int width, int height, unsigned int flags)
{
    GLFWmonitor* monitor = nullptr;

    this->_width = width;
    this->_height = height;

    if (flags & WindowFlag::HIDDEN)
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    if (flags & WindowFlag::FULLSCREEN)
        monitor = glfwGetPrimaryMonitor();
    if (flags & WindowFlag::RESIZABLE)
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->_window = glfwCreateWindow(width, height, name.c_str(), monitor, nullptr);

    glfwMakeContextCurrent(this->_window);

    this->_inputManager = new InputManager;
    this->_inputManager->Init(this->_window);
}

void Window::Destroy()
{
    glfwDestroyWindow(this->_window);
    this->_inputManager->Destroy(this->_window);
}
