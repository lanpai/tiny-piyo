#include <GL/glew.h>

#include "IEngine.h"
#include "IScreen.h"
#include "GLSLProgram.h"
#include "Camera.h"
#include "Input.h"

#include "cstdio"

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
        GLSLProgram _shader;
        Camera _camera;
};

void MainScreen::OnInit()
{
    std::printf("Screen OnInit()\n");
    
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float positions[] =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->_shader.Init("res/shaders/basic.shader");
    this->_camera.Init(640, 480, 90.0f, 0.01f, 1000.0f);
}
void MainScreen::OnDestroy() { std::printf("Screen OnDestroy()\n"); }
void MainScreen::OnEntry() { std::printf("Screen OnEntry()\n"); }
void MainScreen::OnExit() { std::printf("Screen OnExit()\n"); }
void MainScreen::OnUpdate()
{
    float delta = 0.02f;
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
    this->_camera.Update(this->_shader);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

class Engine : public IEngine
{
    virtual void OnPreInit() override;
    virtual void OnPostInit() override;
    virtual void OnUpdate() override;
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
void Engine::OnUpdate()
{
    if (window.ShouldClose())
    {
        this->Destroy();
    }
}
void Engine::OnPreDestroy() { std::printf("Engine OnPreDestroy()\n"); }
void Engine::OnPostDestroy() { std::printf("Engine OnPostDestroy()\n"); }

int main()
{
    Engine engine;
    engine.Run();
    return 0;
}
