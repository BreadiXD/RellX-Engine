//#define TEST
#include "RellXLib.hpp"
int main(int argc,char* argv[]){
    Rellx::Initialize();
    Rellx::GameLoop* gameloop = Rellx::CreateGameLoopInstance();
    gameloop->SetGraphicsAPI(Rellx::GraphicsAPIS::OPENGL33);
    gameloop->SetFps(30);
    gameloop->Initialize();
    Rellx::Servers::DisplayServer* displayServer = gameloop->GetDisplayServer();
    Rellx::Servers::RenderingServer* renderingServer = gameloop->GetRenderingServer();
    Rellx::Servers::WindowInstance* window = displayServer->CreateWindowInstance();
    Rellx::Servers::RenderingContext* context = renderingServer->CreateRenderingContext();

    Rellx::Variants::Vector2i size(800,600);
    displayServer->SetWindowSize(window,size);
    displayServer->SpawnWindow(window);
    renderingServer->AttachContextToWindow(context,window);
    renderingServer->SetBackGroundColor(Rellx::Variants::Color(0.3));
    while (gameloop->IsRunning()){
        gameloop->BeginFrame();
        renderingServer->BeginDraw(context,window);


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
