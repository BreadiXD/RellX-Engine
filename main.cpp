#include "RellXLib.hpp"
#include "string"
int main(int argc,char* argv[]){
    Rellx::Initialize();
    Rellx::GameLoop* gameloop = Rellx::CreateGameLoopInstance();
    gameloop->Initialize();
    Rellx::Servers::DisplayServer* displayServer = gameloop->GetDisplayServer();
    Rellx::Servers::WindowInstance* window = displayServer->CreateWindowInstance();
    Rellx::Variants::Vector2i size(800,600);
    displayServer->SetWindowSize(window,size);
    displayServer->SpawnWindow(window);
    while (gameloop->IsRunning()){
        gameloop->Update();
        // Custom Logic Here
        if (displayServer->WindowShouldClose(window)){
            gameloop->Quit();
        };
    };
    gameloop->CleanUp();
    Rellx::DestroyGameLoopInstance(gameloop);
    Rellx::CleanUp();
    return 0;
}