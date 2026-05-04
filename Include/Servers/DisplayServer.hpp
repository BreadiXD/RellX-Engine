#pragma once
#include "Core/Variants/Vector2.hpp"
#include "Core/Utility.hpp"
// Display Server Is The Manager Of Any Thing You See In Screen ... Used For Creating Windows Etc..
namespace Rellx{
    namespace Servers{
        typedef struct WindowInstance;
        typedef struct DisplayServerData;
        constexpr Rellx::Types::Int32 MAX_WINDOWS = 16;
        struct DisplayServer{
            private:
                WindowInstance* windows[MAX_WINDOWS] = {};
                DisplayServerData* data = nullptr;
            public:
                void Initalize(); // Initalize Function
                void Update(); // Update Function
                void CleanUp(); // CleanUp
                Rellx::Servers::WindowInstance *CreateWindowInstance(); // Create A Window Instance
                void DestroyWindowInstance(Rellx::Servers::WindowInstance* instance); // Destroy Window Instance
                void SetWindowSize(Rellx::Servers::WindowInstance* instance,const Rellx::Variants::Vector2i& size); // Change Window Size
                Rellx::Variants::Vector2i GetWindowSize(Rellx::Servers::WindowInstance* instance) const; // Get Window Size
                void SpawnWindow(Rellx::Servers::WindowInstance* instance); // Create Window
                bool WindowShouldClose(Rellx::Servers::WindowInstance* instance) const;
        };
    };
};