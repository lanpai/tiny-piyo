#include "IEngine.h"

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "IScreen.h"
#include "Window.h"

void IEngine::Run()
{
    // Calling initialization methods
    this->OnPreInit();
    this->_Init();
    this->OnPostInit();

    // Starting engine loop
    this->_isRunning = true;
    //double timeInit = glfwGetTime();
    while (this->_isRunning)
    {
        //double timeFinal = glfwGetTime();
        //double frameTime = timeFinal - timeInit;
        //timeInit = glfwGetTime();

        // Calling engine and screen update methods
        this->OnUpdate();
        if (this->_currentScreen)
            this->_currentScreen->OnUpdate();

        // Drawing and polling inputs
        if (this->_isRunning)
        {
            if (this->_currentScreen)
            {
                glClear(GL_COLOR_BUFFER_BIT);
                this->_currentScreen->OnDraw();

                this->window.SwapBuffers();
                glfwPollEvents();
            }
        }
    }
}

void IEngine::Destroy()
{
    this->_isRunning = false;

    // Calling destruction methods
    this->OnPreDestroy();

    this->_currentScreen->OnExit();
    std::map<const char*, IScreen*>::iterator iter;
    for (iter = this->_screenMap.begin(); iter != this->_screenMap.end(); iter++)
        iter->second->OnDestroy();

    // Garbage-collecting window
    this->window.Destroy();

    // Terminating GLFW
    glfwTerminate();

    // Calling post-destruction methods
    this->OnPostDestroy();
}

void IEngine::ChangeScreen(const std::string& name)
{
    // Exiting current screen if valid
    if (this->_currentScreen)
        this->_currentScreen->OnExit();

    // Switching screen and calling entry method
    this->_currentScreen = this->_screenMap.at(name.c_str());
    this->_currentScreen->OnEntry();
}

void IEngine::AddScreen(const std::string& name, IScreen* screen)
{
    // Adding screen to the screen map and initializing
    this->_screenMap[name.c_str()] = screen;
    screen->SetParentEngine(this);
    screen->OnInit();
}

void IEngine::_Init()
{
    // Initializing GLFW and error checking
    if (!glfwInit())
        std::fprintf(stderr, "Failed to initialize GLFW\n");

    // Initializing window
    this->window.Init(name, width, height, flags);

    // Initializing GLEW and error checking
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
        std::fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    std::printf("%s\n", glGetString(GL_VERSION));
}
