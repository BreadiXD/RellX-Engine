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
                void Initialize(); // Initialize Function
                void BeginFrame();
                void EndFrame();
                void CleanUp(); // CleanUp
            public:
                Rellx::Servers::WindowInstance *CreateWindowInstance(); // Create A Window Instance
                void DestroyWindowInstance(Rellx::Servers::WindowInstance* instance); // Destroy Window Instance
                void SetWindowSize(Rellx::Servers::WindowInstance* instance,const Rellx::Variants::Vector2i& size); // Change Window Size
                Rellx::Variants::Vector2i GetWindowSize(Rellx::Servers::WindowInstance* instance) const; // Get Window Size
                void SpawnWindow(Rellx::Servers::WindowInstance* instance); // Create Window
                bool WindowShouldClose(Rellx::Servers::WindowInstance* instance) const;
                WindowHandler* GetWindowHandler(Rellx::Servers::WindowInstance* instance) const;
            friend class Rellx::GameLoop;
        };
    };
};