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
    void Rellx::GameLoop::Initialize(){
        RELLX_LOG("GameLoop Initializing...")
        displayServer.Initialize();
        RELLX_LOG("GameLoop Initialized!")
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
    void Rellx::GameLoop::Quit(){
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