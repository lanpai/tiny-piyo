#ifndef _I_ENGINE_H
#define _I_ENGINE_H

#include "Window.h"

#include <map>
#include <cstring>

class IScreen;

struct mapCmp
{
    bool operator()(char const*a, char const* b) const
    {
        return std::strcmp(a, b) < 0;
    }
};

class IEngine
{
    public:
        void Run();
        void Destroy();

        Window* GetWindow() { return &this->window; };
    protected:
        virtual void OnPreInit() = 0;
        virtual void OnPostInit() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnPreDestroy() = 0;
        virtual void OnPostDestroy() = 0;

        void ChangeScreen(const std::string& name);
        void AddScreen(const std::string& name, IScreen* screen);

        std::string name;
        int width = 640;
        int height = 480;
        unsigned int flags = 0;
        Window window;
    private:
        bool _isRunning = false;
        std::map<const char*, IScreen*, mapCmp> _screenMap;
        IScreen* _currentScreen = nullptr;

        void _Init();
};

#endif
