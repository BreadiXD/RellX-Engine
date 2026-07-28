#ifdef RELLX_EDITOR
#include "Servers/EditorServer.hpp"
#include "Core/Utility.hpp"
#include "SDL3/SDL.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"
namespace Rellx{
    namespace Servers{
        void Rellx::Servers::EditorServer::Initialize(Rellx::Servers::RenderingContext* context,Rellx::Servers::WindowInstance* window){
            RELLX_LOG("Editor Server Initializing...")
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            ImGui::StyleColorsDark();
            
            SDL_Window* sdl_window = static_cast<SDL_Window*>(gameloop->GetDisplayServer()->GetWindowHandler(window)->ptr);
            
            SDL_GLContext sdl_context = static_cast<SDL_GLContext>(gameloop->GetRenderingServer()->GetContextHandler(context)->ptr);
            
            ImGui_ImplSDL3_InitForOpenGL(sdl_window,sdl_context);
            if (gameloop->GetGraphicsAPI() == Rellx::GraphicsAPIS::OPENGL33){
                ImGui_ImplOpenGL3_Init("#version 330");
            };
            RELLX_LOG("Editor Server Initialized")
        };
        void Rellx::Servers::EditorServer::BeginDraw(){
            
            if (gameloop->GetGraphicsAPI() == Rellx::GraphicsAPIS::OPENGL33){
                ImGui_ImplOpenGL3_NewFrame();
            };
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("States");
            ImGui::Text("FPS: %.2f",1.0f / gameloop->GetDelta());
            ImGui::Text("Delta: %.4f",gameloop->GetDelta());
            ImGui::End();

        };
        void Rellx::Servers::EditorServer::EndDraw(){
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        };


        void Rellx::Servers::EditorServer::BeginFrame(){
            
        };
        void Rellx::Servers::EditorServer::EndFrame(){

        };
        void Rellx::Servers::EditorServer::CleanUp(){

        };
        void Rellx::Servers::EditorServer::ProcesseInput(void* event){
            ImGui_ImplSDL3_ProcessEvent(static_cast<SDL_Event*>(event));
        };
    };
};
#endif