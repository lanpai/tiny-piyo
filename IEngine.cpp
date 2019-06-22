#include "IEngine.h"

#include "tiny-piyo.h"
#include "IScreen.h"
#include "Window.h"

void IEngine::Run()
{
    this->OnPreInit();
    this->_Init();
    this->OnPostInit();

    this->_isRunning = true;
    //double timeInit = glfwGetTime();
    while (this->_isRunning)
    {
        //double timeFinal = glfwGetTime();
        //double frameTime = timeFinal - timeInit;
        //timeInit = glfwGetTime();

        this->OnUpdate();
        if (this->_currentScreen)
            this->_currentScreen->OnUpdate();

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

    this->OnPreDestroy();

    this->_currentScreen->OnExit();
    std::map<const char*, IScreen*>::iterator iter;
    for (iter = this->_screenMap.begin(); iter != this->_screenMap.end(); iter++)
        iter->second->OnDestroy();

    this->window.Destroy();

    glfwTerminate();

    this->OnPostDestroy();
}

void IEngine::ChangeScreen(const std::string& name)
{
    if (this->_currentScreen)
        this->_currentScreen->OnExit();
    this->_currentScreen = this->_screenMap[name.c_str()];
    this->_currentScreen->OnEntry();
}

void IEngine::AddScreen(const std::string& name, IScreen* screen)
{
    this->_screenMap[name.c_str()] = screen;
    screen->SetParentEngine(this);
    screen->OnInit();
}

void IEngine::_Init()
{
    if (!glfwInit())
        std::fprintf(stderr, "Failed to initialize GLFW\n");

    this->window.Init(name, width, height, flags);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
        std::fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    std::printf("%s\n", glGetString(GL_VERSION));
}
