#include "Renderer/OpenGL33RD.hpp"
#include "SDL3/SDL.h"
#include "glad/glad.h"

namespace Rellx{
    namespace Renderer{
        struct OpenGL33Context : public Rellx::Interfaces::IRendererContext{
            SDL_Window* window = nullptr;
            SDL_GLContext context;
            Rellx::Servers::ContextHandler* handler = nullptr;
        };
        void Rellx::Renderer::OpenGL33RD::Initialize(){
            gladLoaded = false;
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,8);
        };
        
        void Rellx::Renderer::OpenGL33RD::BeginDraw(Rellx::Interfaces::IRendererContext* context,Rellx::Servers::WindowHandler* handler){
            tempTargetContext = context;
            tempTargetWindow = handler;
            Rellx::Renderer::OpenGL33Context* gl_context = static_cast<Rellx::Renderer::OpenGL33Context*>(context);
            SDL_Window* window = static_cast<SDL_Window*>(handler->ptr);
            Rellx::Vector2i windowSize;
            SDL_GL_MakeCurrent(window,gl_context->context);
            SDL_GetWindowSize(window,&windowSize.x,&windowSize.y);
            if (!gladLoaded) return;

            glViewport(0,0,windowSize.x,windowSize.y);
            glClearColor(backgroundColor.r,backgroundColor.g,backgroundColor.b,backgroundColor.a);
            glClear(GL_COLOR_BUFFER_BIT);

        };
        void Rellx::Renderer::OpenGL33RD::EndDraw(){
            SDL_Window* window = static_cast<SDL_Window*>(tempTargetWindow->ptr);
            SDL_GL_SwapWindow(window);
            tempTargetContext = nullptr;
            tempTargetWindow = nullptr;
            
        };
        void Rellx::Renderer::OpenGL33RD::BeginFrame(){
            
        };
        void Rellx::Renderer::OpenGL33RD::EndFrame(){
            
        };



        void Rellx::Renderer::OpenGL33RD::CleanUp(){

        };
        void Rellx::Renderer::OpenGL33RD::SetBackGroundColor(const Rellx::Color& color) {
            backgroundColor = color;
        };

        Rellx::Interfaces::IRendererContext* Rellx::Renderer::OpenGL33RD::CreateRenderingContext(){
            return Rellx::Memory::New<Rellx::Renderer::OpenGL33Context>();
        };
        void Rellx::Renderer::OpenGL33RD::DestroyRenderingContext(Rellx::Interfaces::IRendererContext* context){
            Rellx::Renderer::OpenGL33Context* gl_context = static_cast<Rellx::Renderer::OpenGL33Context*>(context);
            if (!gl_context){
                RELLX_LOG_ERROR("Pointer Context Is Invalid!!!")
                return;
            };
            if (!gl_context->context){
                RELLX_LOG_ERROR("OpenGL33 Context Is Invalid!!!")
                return;
            };
            if (!SDL_GL_DestroyContext(gl_context->context)){
                RELLX_LOG_ERROR("Failed Destroy OpenGL Context !!!")
                RELLX_LOG_ERROR(SDL_GetError())

                return;
            }
        };
        void Rellx::Renderer::OpenGL33RD::AttachContextToWindow(Rellx::Interfaces::IRendererContext* context,Rellx::Servers::WindowHandler* handler){
            SDL_Window* window = static_cast<SDL_Window*>(handler->ptr);
            if (!window){
                RELLX_LOG_ERROR("Window Handler Is Invalid !!!")
                return;
            };
            Rellx::Renderer::OpenGL33Context* gl_context = static_cast<Rellx::Renderer::OpenGL33Context*>(context);

            SDL_GLContext glContext = SDL_GL_CreateContext(window);
            if (!glContext){
                RELLX_LOG_ERROR("Cant Create OpenGL Context !!!")
                RELLX_LOG_ERROR(SDL_GetError())
                return;
            };
            if (!gladLoaded){
                gladLoaded = true;
                if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){   
                    gladLoaded = false;
                    RELLX_LOG_ERROR("Cant Load OpenGL Pointers !!!")
                    RELLX_LOG_ERROR(SDL_GetError())
                };
            };
            gl_context->window = window;
            gl_context->context = glContext;
            gl_context->handler =  Rellx::Memory::New<Rellx::Servers::ContextHandler>();
            gl_context->handler->ptr = static_cast<void*>(glContext);
        };
        Rellx::Servers::ContextHandler* Rellx::Renderer::OpenGL33RD::GetContextHandler(Rellx::Interfaces::IRendererContext* context){
            Rellx::Renderer::OpenGL33Context* gl_context = static_cast<Rellx::Renderer::OpenGL33Context*>(context);
            if (gl_context) return gl_context->handler;
            return nullptr;

        };
    };
};