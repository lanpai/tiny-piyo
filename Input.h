#ifndef _TINY_PIYO_INPUT_H
#define _TINY_PIYO_INPUT_H

#include "tiny-piyo.h"

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
        void Init(GLFWwindow* window);
        void Destroy(GLFWwindow* window);

        bool IsKeyDown(int key);
        bool IsKeyPressed(int key);

        static void sKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    private:
        std::map<int, int> _keyMap;
};

#endif
