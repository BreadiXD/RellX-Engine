#pragma once
#include "RellXLib.hpp"
// Display Server Is The Manager Of Any Thing You See In Screen ... Used For Creating Windows Etc..
class Rellx::GameLoop;
namespace Rellx{
    namespace Servers{
        struct WindowInstance;
        struct DisplayServerData;
        struct WindowHandler{void* ptr;};
        constexpr Rellx::Types::Int32 MAX_WINDOWS = 16;
        class DisplayServer{
            private:
                WindowInstance* windows[MAX_WINDOWS] = {};
                DisplayServerData* data = nullptr;
                Rellx::GameLoop* gameloop = nullptr;
                Rellx::VsyncsModes vsyncMode = Rellx::VsyncsModes::OFF;

                void Initialize(); // Initialize Function
                void BeginFrame();
                void EndFrame();
                void CleanUp(); // CleanUp
            public:
                Rellx::Servers::WindowInstance *CreateWindowInstance(); // Create A Window Instance
                void DestroyWindowInstance(Rellx::Servers::WindowInstance* instance); // Destroy Window Instance

                void SetWindowTitle(Rellx::Servers::WindowInstance* instance,const Rellx::String& title); // Change Window Title
                Rellx::String GetWindowTitle(Rellx::Servers::WindowInstance* instance) const; // Get Window Title

                void SetWindowSize(Rellx::Servers::WindowInstance* instance,const Rellx::Vector2i& size); // Change Window Size
                Rellx::Vector2i GetWindowSize(Rellx::Servers::WindowInstance* instance) const; // Get Window Size
                
                void SetVsyncMode(Rellx::VsyncsModes mode) noexcept;
                Rellx::VsyncsModes GetVsyncMode() const noexcept;

                void SpawnWindow(Rellx::Servers::WindowInstance* instance); // Create Window
                bool WindowShouldClose(Rellx::Servers::WindowInstance* instance) const;
                WindowHandler* GetWindowHandler(Rellx::Servers::WindowInstance* instance) const;
            friend class Rellx::GameLoop;
        };
    };
};