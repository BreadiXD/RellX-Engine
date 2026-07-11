#include "Core/GameLoop.hpp"
#include "SDL3/SDL.h"
#include "RellXLib.hpp"
#include "Core/Utility.hpp"
#include <thread>
namespace Rellx{
    class GameLoop;
    namespace Servers{
        struct DisplayServer;
    };
};
namespace Rellx{
    void Rellx::GameLoop::Initialize(){
        RELLX_LOG("GameLoop Initializing...")
        displayServer = Rellx::Memory::New<Rellx::Servers::DisplayServer>();
        renderingServer = Rellx::Memory::New<Rellx::Servers::RenderingServer>();
        displayServer->Initialize();
        displayServer->gameloop = this;
        renderingServer->displayServer = displayServer;
        renderingServer->Initialize(graphicsAPI);
        renderingServer->gameloop = this;
        RELLX_LOG("GameLoop Initialized!")
        running = true;
    };
    void Rellx::GameLoop::BeginFrame(){
        frameStartTime = SDL_GetTicksNS();
        
        displayServer->BeginFrame();
        renderingServer->BeginFrame();
    };
    void Rellx::GameLoop::EndFrame(){
        renderingServer->EndFrame();
        displayServer->EndFrame();
        frameCount++;
        frameEndTime = SDL_GetTicksNS();
        deltaTime = static_cast<double>(frameEndTime - frameStartTime) / 1000000000.0;
        Rellx::Types::Uint64 frameElapsedNS = frameEndTime - frameStartTime;
        if (frameElapsedNS < targetFrameNS){
            Rellx::Types::Uint64 timeLeftNS = targetFrameNS - frameElapsedNS;
            if (timeLeftNS > 2000000){
                SDL_DelayNS(timeLeftNS - 1500000);
            };
            while (SDL_GetTicksNS() - frameStartTime < targetFrameNS){
                std::this_thread::yield();
            };
        };
    };
    void Rellx::GameLoop::CleanUp(){
        RELLX_LOG("GameLoop CleanUp...")
        renderingServer->CleanUp();
        Rellx::Memory::Delete(renderingServer);
        displayServer->CleanUp();
        Rellx::Memory::Delete(displayServer);
        RELLX_LOG("GameLoop CleanUp Completed!")
    };
    void Rellx::GameLoop::Quit(){
        RELLX_LOG("GameLoop Quit!!")
        running = false;
    };
    bool Rellx::GameLoop::IsRunning() const{return running;};
    void Rellx::GameLoop::SetFps(Rellx::Types::Uint64 fps) noexcept{
        Fps = fps;
        targetFrameNS = S2NS / Fps;
    };
    Rellx::Types::Uint64 Rellx::GameLoop::GetFps() const noexcept{return Fps;};

    void Rellx::GameLoop::SetGraphicsAPI(Rellx::GraphicsAPIS api) noexcept{graphicsAPI = api;};
    Rellx::GraphicsAPIS Rellx::GameLoop::GetGraphicsAPI() const noexcept{return graphicsAPI;};
    double Rellx::GameLoop::GetDelta() const noexcept{return deltaTime;};
    Rellx::Types::Uint64 Rellx::GameLoop::GetFrameCount() const noexcept{return frameCount;};
    Rellx::Servers::DisplayServer* Rellx::GameLoop::GetDisplayServer() const {
        return displayServer;
    };
    Rellx::Servers::RenderingServer* Rellx::GameLoop::GetRenderingServer() const {
        return renderingServer;
    };  
};