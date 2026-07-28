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
        struct RenderingContext;
        struct ContextHandler{void* ptr;};

        constexpr Rellx::Types::Int32 MAX_CONTEXTS = 16;
        class RenderingServer{
            private:
                Rellx::Color backgroundColor = Rellx::Color(1.0f);
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
                void SetBackGroundColor(const Rellx::Color& color);
                Rellx::Color GetBackGroundColor() const;
                ContextHandler* GetContextHandler(Rellx::Servers::RenderingContext* context) const;
            friend class Rellx::GameLoop;
            
        };
    };
};