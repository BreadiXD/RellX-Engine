//#define TEST
#include "RellXLib.hpp"

int main(){
    Rellx::Initialize();
    Rellx::GameLoop* gameloop = Rellx::CreateGameLoopInstance();
    gameloop->SetGraphicsAPI(Rellx::GraphicsAPIS::OPENGL33);
    gameloop->SetVsyncMode(Rellx::VsyncsModes::OFF);
    gameloop->SetFps(60);
    gameloop->Initialize();
    Rellx::Servers::DisplayServer* displayServer = gameloop->GetDisplayServer();
    Rellx::Servers::RenderingServer* renderingServer = gameloop->GetRenderingServer();
    Rellx::Servers::WindowInstance* window = displayServer->CreateWindowInstance();
    Rellx::Servers::RenderingContext* context = renderingServer->CreateRenderingContext();
    Rellx::Vector2i size(800,600);
    Rellx::String title = "Rellx Engine";
    displayServer->SetWindowSize(window,size);
    displayServer->SetWindowTitle(window,title);
    displayServer->SpawnWindow(window);
    renderingServer->AttachContextToWindow(context,window);
    renderingServer->SetBackGroundColor(Rellx::Color(0.3));

    #ifdef RELLX_EDITOR
    Rellx::Servers::EditorServer* editorServer = gameloop->GetEditorServer();
    editorServer->Initialize(context,window);
    #endif
    while (gameloop->IsRunning()){
        gameloop->BeginFrame();
        renderingServer->BeginDraw(context,window);
        #ifdef RELLX_EDITOR
        editorServer->BeginDraw();
        
        editorServer->EndDraw();
        #endif
        renderingServer->EndDraw();
        if (displayServer->WindowShouldClose(window)) gameloop->Quit();
        gameloop->EndFrame();
    };
    renderingServer->DestroyRenderingContext(context);
    displayServer->DestroyWindowInstance(window);
    gameloop->CleanUp();
    Rellx::DestroyGameLoopInstance(gameloop);
    Rellx::CleanUp();
    return 0;
}
