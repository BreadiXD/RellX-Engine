#include "Core/GameLoop.hpp"
#include "SDL3/SDL.h"
#include "RellXLib.hpp"
#include "Core/Utility.hpp"
namespace Rellx{
    class GameLoop;
    namespace Servers{
        struct DisplayServer;
    };
};

namespace Rellx{
    void Rellx::GameLoop::Initalize(){
        RELLX_LOG("GameLoop Initalizing...")
        displayServer.Initalize();
        RELLX_LOG("GameLoop Initalized!")
        running = true;
    };
    void Rellx::GameLoop::Update(){
        displayServer.Update();
    };
    void Rellx::GameLoop::CleanUp(){
        RELLX_LOG("GameLoop CleanUp...")
        displayServer.CleanUp();
        RELLX_LOG("GameLoop CleanUp Completed!")
    };
    void Rellx::GameLoop::Quite(){
        RELLX_LOG("GameLoop Quite!!")
        running = false;
    };
    bool Rellx::GameLoop::IsRunning() const{
        return running;
    };
    Rellx::Servers::DisplayServer* Rellx::GameLoop::GetDisplayServer() {
        return &displayServer;
    };
};