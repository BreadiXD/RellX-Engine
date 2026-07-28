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
        inputServer = Rellx::Memory::New<Rellx::Servers::InputServer>();
        #ifdef RELLX_EDITOR
        editorServer = Rellx::Memory::New<Rellx::Servers::EditorServer>();
        #endif        
        displayServer->gameloop = this;
        displayServer->Initialize();
        renderingServer->displayServer = displayServer;
        renderingServer->gameloop = this;
        renderingServer->Initialize(graphicsAPI);
        inputServer->gameloop = this;
        inputServer->Initialize();
        #ifdef RELLX_EDITOR
        editorServer->gameloop = this;
        #endif
        targetFrameNS = S2NS / Fps;
        RELLX_LOG("GameLoop Initialized!")
        running = true;
    };
    void Rellx::GameLoop::BeginFrame(){
        frameStartTime = SDL_GetTicksNS();
        displayServer->BeginFrame();
        renderingServer->BeginFrame();
        inputServer->BeginFrame();
        #ifdef RELLX_EDITOR
        editorServer->BeginFrame();
        #endif
        
    };
    void Rellx::GameLoop::EndFrame(){

        inputServer->EndFrame();
        renderingServer->EndFrame();
        displayServer->EndFrame();
        #ifdef RELLX_EDITOR
        editorServer->EndFrame();
        #endif
        
        frameCount++;
        Rellx::Types::Uint64 frameElapsedNS = SDL_GetTicksNS() - frameStartTime;
        if (frameElapsedNS < targetFrameNS){
            Rellx::Types::Uint64 timeLeftNS = targetFrameNS - frameElapsedNS;
            if (timeLeftNS > 2000000){
                SDL_DelayNS(timeLeftNS - 1500000);
            };
            while (SDL_GetTicksNS() - frameStartTime < targetFrameNS){
                std::this_thread::yield();
            };
        };
        frameEndTime = SDL_GetTicksNS();
        deltaTime = static_cast<Rellx::Types::Reel>(frameEndTime - frameStartTime) / 1000000000.0f;
    };
    void Rellx::GameLoop::CleanUp(){
        RELLX_LOG("GameLoop CleanUp...")
        renderingServer->CleanUp();
        Rellx::Memory::Delete(renderingServer);
        displayServer->CleanUp();
        Rellx::Memory::Delete(displayServer);
        inputServer->CleanUp();
        Rellx::Memory::Delete(inputServer);
        #ifdef RELLX_EDITOR
        editorServer->CleanUp();
        Rellx::Memory::Delete(editorServer);
        #endif        
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
    Rellx::Types::Reel Rellx::GameLoop::GetDelta() const noexcept{return deltaTime;};
    Rellx::Types::Uint64 Rellx::GameLoop::GetFrameCount() const noexcept{return frameCount;};

    void Rellx::GameLoop::SetVsyncMode(Rellx::VsyncsModes mode) noexcept{
        if (!displayServer) return;
        displayServer->SetVsyncMode(mode);
    };
    Rellx::VsyncsModes Rellx::GameLoop::GetVsyncMode() const noexcept{
        if (!displayServer) return Rellx::VsyncsModes::OFF;
        return displayServer->GetVsyncMode();
    };
    Rellx::Servers::DisplayServer* Rellx::GameLoop::GetDisplayServer() const {
        return displayServer;
    };
    Rellx::Servers::RenderingServer* Rellx::GameLoop::GetRenderingServer() const {
        return renderingServer;
    };
    Rellx::Servers::InputServer* Rellx::GameLoop::GetInputServer() const{
        return inputServer;
    };
    #ifdef RELLX_EDITOR
    Rellx::Servers::EditorServer* Rellx::GameLoop::GetEditorServer() const{
        return editorServer;
    };
    #endif
};