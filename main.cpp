#include "IEngine.h"
#include "IScreen.h"
#include "Camera.h"
#include "Input.h"
#include "Shaders.h"

#include <cstdio>
#include <cstdlib>

class MainScreen : public IScreen
{
    protected:
        virtual void OnInit() override;
        virtual void OnDestroy() override;
        virtual void OnEntry() override;
        virtual void OnExit() override;
        virtual void OnUpdate() override;
        virtual void OnDraw() override;

    private:
        BasicGeoShader _geoShader;
        Camera _camera;
};

void MainScreen::OnInit()
{
    std::printf("Screen OnInit()\n");

    this->_geoShader.Init();
    this->_camera.Init(640, 480, 90.0f, 0.01f, 1000.0f);

    this->GetInputManager()->LockMouse();
}
void MainScreen::OnDestroy()
{
    std::printf("Screen OnDestroy()\n");
    this->_geoShader.Destroy();
}
void MainScreen::OnEntry() { std::printf("Screen OnEntry()\n"); }
void MainScreen::OnExit() { std::printf("Screen OnExit()\n"); }
void MainScreen::OnUpdate()
{
    float2 cursorPos = this->GetInputManager()->GetCursorPos();
    std::printf("cursor position = (%f, %f)\n", cursorPos.x, cursorPos.y);
    float delta = this->engine->GetDelta() / 7;
    if (this->GetInputManager()->IsKeyDown(GLFW_KEY_UP))
        this->_camera.Rotate(0.0f, delta, 0.0f);
    if (this->GetInputManager()->IsKeyDown(GLFW_KEY_LEFT))
        this->_camera.Rotate(-delta, 0.0f, 0.0f);
    if (this->GetInputManager()->IsKeyDown(GLFW_KEY_DOWN))
        this->_camera.Rotate(0.0f, -delta, 0.0f);
    if (this->GetInputManager()->IsKeyDown(GLFW_KEY_RIGHT))
        this->_camera.Rotate(delta, 0.0f, 0.0f);
    if (this->GetInputManager()->IsKeyDown(GLFW_KEY_W))
        this->_camera.Translate(0.0f, 0.0f, delta);
    if (this->GetInputManager()->IsKeyDown(GLFW_KEY_A))
        this->_camera.Translate(-delta, 0.0f, 0.0f);
    if (this->GetInputManager()->IsKeyDown(GLFW_KEY_S))
        this->_camera.Translate(0.0f, 0.0f, -delta);
    if (this->GetInputManager()->IsKeyDown(GLFW_KEY_D))
        this->_camera.Translate(delta, 0.0f, 0.0f);
    if (this->GetInputManager()->IsKeyDown(GLFW_KEY_Q))
        this->_camera.Translate(0.0f, delta, 0.0f);
    if (this->GetInputManager()->IsKeyDown(GLFW_KEY_E))
        this->_camera.Translate(0.0f, -delta, 0.0f);
}
void MainScreen::OnDraw()
{
    this->_camera.Update(this->_geoShader);
    this->_geoShader.DrawTri(
        Vertex3D(
            float3(-0.5f, -0.5f,  0.0f), 
            ColorRGBA8(0, 255, 0, 255)
        ),
        Vertex3D(
            float3( 0.5f,  0.5f,  0.0f),
            ColorRGBA8(0, 0, 255, 255)
        ),
        Vertex3D(
            float3( 0.5f, -0.5f,  0.0f),
            ColorRGBA8(255, 0, 0, 255)
        )
    );
    this->_geoShader.DrawTri(
        Vertex3D(
            float3(-0.5f, -0.5f,  0.0f), 
            ColorRGBA8(0, 255, 0, 120)
        ),
        Vertex3D(
            float3(-0.5f,  0.5f,  0.0f),
            ColorRGBA8(255, 0, 0, 120)
        ),
        Vertex3D(
            float3( 0.5f,  0.5f,  0.0f),
            ColorRGBA8(0, 0, 255, 120)
        )
    );
    this->_geoShader.DrawQuad(
        Vertex3D(
            float3(-1.0f,  1.0f, 5.0f),
            ColorRGBA8(0, 255, 0, 255)
        ),
        Vertex3D(
            float3( 1.0f,  1.0f, 5.0f),
            ColorRGBA8(0, 255, 0, 255)
        ),
        Vertex3D(
            float3( 1.0f, -1.0f, 5.0f),
            ColorRGBA8(0, 255, 0, 255)
        ),
        Vertex3D(
            float3(-1.0f, -1.0f, 5.0f),
            ColorRGBA8(0, 255, 0, 255)
        )
    );
    this->_geoShader.End();
    this->_geoShader.Render();
}

class Engine : public IEngine
{
    virtual void OnPreInit() override;
    virtual void OnPostInit() override;
    virtual void OnPreDestroy() override;
    virtual void OnPostDestroy() override;
};
void Engine::OnPreInit()
{
    std::printf("Engine OnPreInit()\n");

    this->name = "i3-floating";
}
void Engine::OnPostInit() {
    std::printf("Engine OnPostInit()\n");

    this->AddScreen("main", new MainScreen);
    this->ChangeScreen("main");
}
void Engine::OnPreDestroy() { std::printf("Engine OnPreDestroy()\n"); }
void Engine::OnPostDestroy() { std::printf("Engine OnPostDestroy()\n"); }

int main()
{
    Engine engine;
    engine.Run();

    system("PAUSE");

    return 0;
}
