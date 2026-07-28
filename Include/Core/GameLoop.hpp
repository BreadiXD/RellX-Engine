#pragma once
#include "RellXLib.hpp"
/*
    GameLoop Is Main Application Startup That Will Manage Every Action Happend In The Program
    And Give A Way To Control Low Level Stuff With Readable APIs
*/
namespace Rellx{
    namespace Servers{
        class DisplayServer;
        class RenderingServer;
        class InputServer;
        class EditorServer;
    };  
};
namespace Rellx{
    class GameLoop{
        private:
            Rellx::Types::Reel deltaTime = 0.0f;
            Rellx::Types::Uint64 frameCount = 0u;
            Rellx::Types::Uint64 frameStartTime = 0u;
            Rellx::Types::Uint64 frameEndTime = 0u;

            const Rellx::Types::Uint64 S2NS = 1000000000;
            Rellx::Types::Uint64 targetFrameNS = 0;
            Rellx::Servers::DisplayServer* displayServer = nullptr;
            Rellx::Servers::RenderingServer* renderingServer = nullptr;
            Rellx::Servers::InputServer* inputServer = nullptr;
            #ifdef RELLX_EDITOR
            Rellx::Servers::EditorServer* editorServer = nullptr;
            #endif
            Rellx::Types::Uint64 Fps = 30;
            bool running = false;
            Rellx::GraphicsAPIS graphicsAPI = Rellx::GraphicsAPIS::NONE;
        public:
            void Initialize();
            void BeginFrame();
            void EndFrame();
            void CleanUp();
            void Quit();
            bool IsRunning() const;

            void SetFps(Rellx::Types::Uint64 fps) noexcept;
            Rellx::Types::Uint64 GetFps() const noexcept;
            void SetVsyncMode(Rellx::VsyncsModes mode) noexcept;
            Rellx::VsyncsModes GetVsyncMode() const noexcept;
            void SetGraphicsAPI(Rellx::GraphicsAPIS api) noexcept;
            Rellx::GraphicsAPIS GetGraphicsAPI() const noexcept;

            Rellx::Types::Reel GetDelta() const noexcept;
            Rellx::Types::Uint64 GetFrameCount() const noexcept;
            Rellx::Servers::DisplayServer* GetDisplayServer() const;
            Rellx::Servers::RenderingServer* GetRenderingServer() const;
            Rellx::Servers::InputServer* GetInputServer() const;
            #ifdef RELLX_EDITOR
            Rellx::Servers::EditorServer* GetEditorServer() const;
            #endif

    };    
};