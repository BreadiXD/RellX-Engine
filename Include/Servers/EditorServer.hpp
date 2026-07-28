#ifdef RELLX_EDITOR
#pragma once
#include "RellXLib.hpp"


class Rellx::GameLoop;
class Rellx::Servers::DisplayServer;
namespace Rellx{
    namespace Servers{
        class EditorServer{
            private:
                Rellx::GameLoop* gameloop = nullptr;
                void BeginFrame();
                void EndFrame();
                void CleanUp();
                void ProcesseInput(void* event);
            public:
                void Initialize(Rellx::Servers::RenderingContext* context,Rellx::Servers::WindowInstance* window);
                void BeginDraw();
                void EndDraw();
            friend class Rellx::GameLoop;
            friend class Rellx::Servers::DisplayServer;
        };
    };
};


#endif