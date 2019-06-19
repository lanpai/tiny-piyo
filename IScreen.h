#ifndef _I_SCREEN_H
#define _I_SCREEN_H

#include "IEngine.h"
#include "Window.h"
#include "Input.h"

class IScreen
{
    friend class IEngine;

    protected:
        virtual void OnInit() = 0;
        virtual void OnDestroy() = 0;

        virtual void OnEntry() = 0;
        virtual void OnExit() = 0;

        virtual void OnUpdate() = 0;
        virtual void OnDraw() = 0;

        void SetParentEngine(IEngine* parent) { this->engine = parent; };

        Window* GetWindow() { return this->engine->GetWindow(); };
        InputManager* GetInputManager() { return this->GetWindow()->GetInputManager(); };

        IEngine* engine = nullptr;
};

#endif
