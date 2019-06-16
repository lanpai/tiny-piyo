#ifndef _WINDOW_H
#define _WINDOW_H

#include <GLFW/glfw3.h>

#include <string>

enum WindowFlag
{
    HIDDEN = 0x1,
    FULLSCREEN = 0x2,
    RESIZABLE = 0x4
};

class Window
{
    public:
        void Init(const std::string& name, int width, int height, unsigned int flags = 0);

        bool ShouldClose() { return glfwWindowShouldClose(this->_window); };
        unsigned int GetKey(unsigned int key) { return glfwGetKey(this->_window, key); };
        void SwapBuffers() { glfwSwapBuffers(this->_window); };
    private:
        GLFWwindow* _window;

        int _width, _height;
};

#endif
