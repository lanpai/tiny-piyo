#include "Input.h"

#include <cstdio>

void InputManager::Init(Window* window)
{
    this->_window = window;

    // Setting the key event callback
    glfwSetWindowUserPointer(this->_window->GetWindow(), this);
    glfwSetKeyCallback(this->_window->GetWindow(), sKeyCallback);
    glfwSetCursorPosCallback(this->_window->GetWindow(), sCursorPosCallback);

    // Setting a default value for the key map
    for (int i = 0; i <= 348; i++)
        this->_keyMap[i] = KeyState::UP;
}

void InputManager::Destroy()
{
    // Unsetting the key event callback
    glfwSetKeyCallback(this->_window->GetWindow(), nullptr);
}

bool InputManager::IsKeyDown(int key)
{
    // If the key is in either a down or press state, return true
    if (this->_keyMap.at(key) == KeyState::DOWN || this->_keyMap.at(key) == KeyState::PRESS)
    {
        return true;
    }
    return false;
}

bool InputManager::IsKeyPressed(int key)
{
    // If the key is in a press state, return true
    if (this->_keyMap.at(key) == KeyState::PRESS)
    {
        this->_keyMap.at(key) = KeyState::DOWN;
        return true;
    }
    return false;
}

void InputManager::sKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Calling the non-static key callback from this static method
    InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    inputManager->KeyCallback(window, key, scancode, action, mods);
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    this->_keyMap[key] = action;
}

void InputManager::sCursorPosCallback(GLFWwindow* window, double x, double y)
{
    // Calling the non-static cursor pos callback from this static method
    InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    inputManager->CursorPosCallback(window, x, y);
}

void InputManager::CursorPosCallback(GLFWwindow* window, double x, double y)
{
    this->_x = x;
    this->_y = y;
}