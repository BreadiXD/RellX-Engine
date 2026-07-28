#pragma once
#include "Interfaces/IRenderer.hpp"
namespace Rellx{
    namespace Renderer{
        class OpenGL33RD : public Rellx::Interfaces::IRenderer{
            private:
                bool gladLoaded = false;
                Rellx::Color backgroundColor = Rellx::Color(1.0f);
                Rellx::Interfaces::IRendererContext* tempTargetContext = nullptr;
                Rellx::Servers::WindowHandler* tempTargetWindow = nullptr;
            protected:
                void Initialize() override;
                void BeginDraw(Rellx::Interfaces::IRendererContext* context,Rellx::Servers::WindowHandler* handler = nullptr) override;
                void EndDraw() override;
                void BeginFrame() override;
                void EndFrame() override;
                void CleanUp() override;
            public:
                void SetBackGroundColor(const Rellx::Color& color) override;
                Rellx::Interfaces::IRendererContext* CreateRenderingContext() override;
                void DestroyRenderingContext(Rellx::Interfaces::IRendererContext* context) override;
                void AttachContextToWindow(Rellx::Interfaces::IRendererContext* context,Rellx::Servers::WindowHandler* handler) override;
                Rellx::Servers::ContextHandler* GetContextHandler(Rellx::Interfaces::IRendererContext* context) override;

        };
    };
};