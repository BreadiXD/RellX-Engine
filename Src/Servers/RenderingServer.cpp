#include "Servers/RenderingServer.hpp"
#include "Servers/DisplayServer.hpp"
#include "Core/Utility.hpp"
#include "SDL3/SDL.h"
#include "glad/glad.h"
namespace Rellx{
    namespace Servers{
        struct RenderingContext{
            Rellx::Interfaces::IRendererContext* context;
        };
        void Rellx::Servers::RenderingServer::Initialize(Rellx::GraphicsAPIS api){
            RELLX_LOG("Rendering Server Initializing...")
            currentAPI = api;
            for (Rellx::Types::Int32 i = 0; i < MAX_CONTEXTS; i++)contexts[i] = nullptr;
            if (Rellx::GraphicsAPIS::OPENGL33 == currentAPI){
                renderer = Rellx::Memory::New<Rellx::Renderer::OpenGL33RD>();
                if (!renderer){
                    RELLX_LOG_ERROR("Cant Create Rendering Device");
                    return;
                };
                RELLX_LOG("Rendering Device Created With OpenGL33!!");    
            };
            renderer->Initialize();
            RELLX_LOG("Rendering Server Initialized")
        };
        void Rellx::Servers::RenderingServer::BeginFrame(){
            renderer->BeginFrame();
        };
        void Rellx::Servers::RenderingServer::EndFrame(){
            renderer->EndFrame();
        };
        void Rellx::Servers::RenderingServer::BeginDraw(Rellx::Servers::RenderingContext* context,Rellx::Servers::WindowInstance* window){
            renderer->BeginDraw(context->context,displayServer->GetWindowHandler(window));
        };
        void Rellx::Servers::RenderingServer::EndDraw(){
            renderer->EndDraw();
        };
        void Rellx::Servers::RenderingServer::CleanUp(){
            RELLX_LOG("Rendering Server CleanUp...")
            for (Rellx::Types::Int32 i = 0; i < MAX_CONTEXTS; i++){
                if (contexts[i]) DestroyRenderingContext(contexts[i]);
            };
            if (renderer){
                renderer->CleanUp();
                Rellx::Memory::Delete(renderer);
            };
            RELLX_LOG("Rendering Server CleanUp Completed!")
        };
        Rellx::Servers::RenderingContext* Rellx::Servers::RenderingServer::CreateRenderingContext(){
            Rellx::Servers::RenderingContext* ptr = nullptr;
            for (Rellx::Types::Int32 i = 0; i < MAX_CONTEXTS; i++){
                if (contexts[i])continue;
                ptr = Rellx::Memory::New<Rellx::Servers::RenderingContext>();
                if (ptr){
                    ptr->context = renderer->CreateRenderingContext();
                    ptr->context->ID = i;
                    contexts[i] = ptr;
                };
                break;
            };
            if (!ptr){
                RELLX_LOG_ERROR("Cant Create Rendering Context !!!")
                return nullptr;
            };

            return ptr;
        };
        void Rellx::Servers::RenderingServer::DestroyRenderingContext(Rellx::Servers::RenderingContext* context){
            if (!context){
                RELLX_LOG_ERROR("Rendering Context Is Invalid!!!")
                return;
            };
            if (!context->context){
                RELLX_LOG_ERROR("Rendering Context Is Invalid!!!")
                return;
            };
            renderer->DestroyRenderingContext(context->context);
            
            contexts[context->context->ID] = nullptr;
            RELLX_LOG("Destroy Rendering Context ID %d",context->context->ID)
            Rellx::Memory::Delete(context->context);
            Rellx::Memory::Delete(context);
        };
        void Rellx::Servers::RenderingServer::AttachContextToWindow(Rellx::Servers::RenderingContext* context,Rellx::Servers::WindowInstance* window){
            renderer->AttachContextToWindow(context->context,displayServer->GetWindowHandler(window));
            RELLX_LOG("Attach Rendering Context ID %d",context->context->ID)
        };
        void Rellx::Servers::RenderingServer::SetBackGroundColor(const Rellx::Color& color) {
            backgroundColor = color;
            if (renderer)renderer->SetBackGroundColor(backgroundColor);
        };
        Rellx::Color Rellx::Servers::RenderingServer::GetBackGroundColor() const {
            return backgroundColor;
        };
        Rellx::Servers::ContextHandler* Rellx::Servers::RenderingServer::GetContextHandler(Rellx::Servers::RenderingContext* context) const{
            if (renderer) return renderer->GetContextHandler(context->context);
            return nullptr;
        };


    };
};