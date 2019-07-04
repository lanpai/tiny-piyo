#ifndef _TINY_PIYO_I_ENGINE_H
#define _TINY_PIYO_I_ENGINE_H

#include "Window.h"
#include "Definitions.h"

#include <map>
#include <cstring>
#include <vector>

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

        double GetFrameTime() { return this->_frameTime; }
        double GetFrameRate() { return (double)(1 / this->_frameTime) * 1000; }
        void SetDesiredFrameTime(double frameTime) { this->_desiredFrameTime = frameTime; }
        void SetDesiredFrameRate(double fps) { this->_desiredFrameTime = (double)1 / (fps * 1000); }
        double GetDesiredFrameTime() { return this->_desiredFrameTime; }
        double GetDelta() { return this->_desiredFrameTime / this->_frameTime; }

        Window* GetWindow() { return &this->window; };
    protected:
        virtual void OnPreInit() {};
        virtual void OnPostInit() {};
        virtual void OnUpdate() {};
        virtual void OnPreDestroy() {};
        virtual void OnPostDestroy() {};

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

        double _frameTime;
        double _desiredFrameTime = (double)1 / 60000; // 60 FPS
        std::vector<double> _frameTimes;

        void _Init();
};

#endif
