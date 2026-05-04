#include "iostream"
#include "RellXLib.hpp"
int main(int argc,char* argv[]){
    Rellx::GameLoop* gameloop = Rellx::CreateGameLoopInstance();
    gameloop->Initalize();

    Rellx::Servers::DisplayServer* displayServer = gameloop->GetDisplayServer();
    Rellx::Servers::WindowInstance* window = displayServer->Window_CreateWindowInstance();
    Rellx::Variants::Vector2i size(800,600);
    displayServer->Window_SetWindowSize(window,size);
    displayServer->Window_SpwanWindow(window);
    while (gameloop->IsRunning()){
        gameloop->Update();
        // Custom Logic Here
        if (displayServer->Window_WindowShouldClose(window)){
            gameloop->Quite();
        };
    };
    gameloop->CleanUp();
    return 0;
}