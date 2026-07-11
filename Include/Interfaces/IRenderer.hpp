#pragma once
#include "RellXLib.hpp"
namespace Rellx{
    namespace Servers{
        struct WindowHandler;
    };
};
namespace Rellx{
    namespace Interfaces{
        struct IRendererContext{
            Rellx::Types::Int32 ID = 0;
        };
        class IRenderer{
            protected:
                virtual void Initialize() = 0;
                virtual void BeginDraw(Rellx::Interfaces::IRendererContext* context,Rellx::Servers::WindowHandler* handler) = 0;
                virtual void EndDraw() = 0;

                virtual void BeginFrame() = 0;
                virtual void EndFrame() = 0;
                
                virtual void CleanUp() = 0;
            public:
                virtual void SetBackGroundColor(const Rellx::Variants::Color& color) = 0;
                virtual Rellx::Interfaces::IRendererContext* CreateRenderingContext() = 0;
                virtual void DestroyRenderingContext(Rellx::Interfaces::IRendererContext* context) = 0;
                virtual void AttachContextToWindow(Rellx::Interfaces::IRendererContext* context,Rellx::Servers::WindowHandler* handler) = 0;

            friend class Rellx::Servers::RenderingServer;
        };
    };
};