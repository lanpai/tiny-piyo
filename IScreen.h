#ifndef _I_SCREEN_H
#define _I_SCREEN_H

#include "IEngine.h"
#include "Window.h"

class InputManager;

class IScreen
{
    friend class IEngine;

    protected:
        virtual void OnInit() {};
        virtual void OnDestroy() {};

        virtual void OnEntry() {};
        virtual void OnExit() {};

        virtual void OnUpdate() {};
        virtual void OnDraw() {};

        void SetParentEngine(IEngine* parent) { this->engine = parent; };

        Window* GetWindow() { return this->engine->GetWindow(); };
        InputManager* GetInputManager() { return this->GetWindow()->GetInputManager(); };

        IEngine* engine = nullptr;
};

#endif
