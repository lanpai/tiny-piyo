#ifndef _WINDOW_H
#define _WINDOW_H

#include "tiny-piyo.h"
#include "Input.h"

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
        void Destroy();

        bool ShouldClose() { return glfwWindowShouldClose(this->_window); };
        unsigned int GetKey(unsigned int key) { return glfwGetKey(this->_window, key); };
        void SwapBuffers() { glfwSwapBuffers(this->_window); };

        int GetScreenWidth() { return this->_width; };
        int GetScreenHeight() { return this->_height; };

        void SetScreenTitle(const std::string& name) { glfwSetWindowTitle(this->_window, name.c_str()); };

        InputManager* GetInputManager() { return this->_inputManager; };
    private:
        GLFWwindow* _window;
        InputManager* _inputManager;

        int _width, _height;
};

#endif
