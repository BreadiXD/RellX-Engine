#pragma once
#include "RellXLib.hpp"
class Rellx::GameLoop;
namespace Rellx{
    namespace Servers{
        struct DisplayServer;
    };
};
namespace Rellx{
    namespace Servers{
        typedef struct RenderingContext;
        constexpr Rellx::Types::Int32 MAX_CONTEXTS = 16;
        class RenderingServer{
            private:
                Rellx::Variants::Color backgroundColor = Rellx::Variants::Color(1.0f);
                RenderingContext* contexts[MAX_CONTEXTS] = {};
                Rellx::GameLoop* gameloop = nullptr;
                Rellx::Interfaces::IRenderer* renderer = nullptr;
                Rellx::GraphicsAPIS currentAPI;
                Rellx::Servers::DisplayServer* displayServer = nullptr;

                void Initialize(Rellx::GraphicsAPIS api);
                void BeginFrame();
                void EndFrame();
                void CleanUp();
            public:
                void BeginDraw(Rellx::Servers::RenderingContext* context,Rellx::Servers::WindowInstance* window);
                void EndDraw();
                RenderingContext* CreateRenderingContext();
                void DestroyRenderingContext(Rellx::Servers::RenderingContext* context);
                void AttachContextToWindow(Rellx::Servers::RenderingContext* context,Rellx::Servers::WindowInstance* window);
                void SetBackGroundColor(const Rellx::Variants::Color& color);
                Rellx::Variants::Color GetBackGroundColor() const;
            friend class Rellx::GameLoop;
            
        };
    };
};