#ifndef _TINY_PIYO_INPUT_H
#define _TINY_PIYO_INPUT_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Types.h"

#include <map>

class Window;

enum KeyState
{
    UP = 0,
    PRESS = 1,
    DOWN = 2
};

class InputManager
{
    public:
        void Init(Window* window);
        void Destroy();

        bool IsKeyDown(int key);
        bool IsKeyPressed(int key);

        void LockMouse() { glfwSetInputMode(this->_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
        void UnlockMouse() { glfwSetInputMode(this->_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

        float2 GetCursorPos() { return float2(this->_x, this->_y); }

        static void sKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void sCursorPosCallback(GLFWwindow* window, double x, double y);
        void CursorPosCallback(GLFWwindow* window, double x, double y);
    private:
        Window* _window;
        std::map<int, int> _keyMap;

        double _x;
        double _y;
};

#endif
