#include "Input.h"

#include <cstdio>

void InputManager::Init(GLFWwindow* window)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, sKeyCallback);
}

void InputManager::Destroy(GLFWwindow* window)
{
    glfwSetKeyCallback(window, nullptr);
}

bool InputManager::IsKeyDown(int key)
{
    if (this->_keyMap[key] == KeyState::DOWN || this->_keyMap[key] == KeyState::PRESS)
    {
        return true;
    }
    return false;
}

bool InputManager::IsKeyPressed(int key)
{
    if (this->_keyMap[key] == KeyState::PRESS)
    {
        this->_keyMap[key] = KeyState::DOWN;
        return true;
    }
    return false;
}

void InputManager::sKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    inputManager->KeyCallback(window, key, scancode, action, mods);
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    this->_keyMap[key] = action;
}
