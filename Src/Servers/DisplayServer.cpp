#include "Servers/DisplayServer.hpp"
#include "Core/Utility.hpp"
#include "SDL3/SDL.h"
namespace Rellx{
    namespace Servers{
        struct DisplayServerData{
            SDL_Event event;
        };
        struct WindowInstance{
            WindowHandler* windowHanlder = nullptr;
            SDL_Window* window = nullptr;
            Rellx::Types::Int32 ID = 0;
            Rellx::Vector2i size = Rellx::Vector2i(640,360);
            Rellx::String title = "Rellx Engine";
            bool shouldClose = false;
        };
        void Rellx::Servers::DisplayServer::Initialize(){
            RELLX_LOG("Display Server Initializing...")
            for (Rellx::Types::Int32 i = 0; i < MAX_WINDOWS; i++)windows[i] = nullptr;
            data = Rellx::Memory::New<Rellx::Servers::DisplayServerData>();
            RELLX_LOG("Display Server Initialized")
        };
        void Rellx::Servers::DisplayServer::BeginFrame(){
            while(SDL_PollEvent(&data->event)){
                #ifdef RELLX_EDITOR
                gameloop->GetEditorServer()->ProcesseInput(static_cast<void*>(&data->event));
                #endif
                if (data->event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED){
                    for (Rellx::Types::Int32 i = 0; i < MAX_WINDOWS; i++){
                        if (!windows[i])continue;
                        if (SDL_GetWindowID(windows[i]->window) == data->event.window.windowID){
                            windows[i]->shouldClose = true;                        
                            RELLX_LOG("Window Should Close ID %d",i)
                        };    
                    };
                } else if (data->event.type == SDL_EVENT_WINDOW_RESIZED){
                    for (Rellx::Types::Int32 i = 0; i < MAX_WINDOWS; i++){
                        if (!windows[i])continue;
                        if (SDL_GetWindowID(windows[i]->window) == data->event.window.windowID){
                            windows[i]->size.x = data->event.window.data1;
                            windows[i]->size.y = data->event.window.data2;
                            RELLX_LOG("Window ID %d Resized %dx%d",i,windows[i]->size.x,windows[i]->size.y)
                        };
                    };
                };
            };
        };
        void Rellx::Servers::DisplayServer::EndFrame(){
            
        };
        void Rellx::Servers::DisplayServer::CleanUp(){
            RELLX_LOG("Display Server CleanUp...")
            for (Rellx::Types::Int32 i = 0; i < MAX_WINDOWS; i++){
                if (windows[i]) DestroyWindowInstance(windows[i]);
            };
            Rellx::Memory::Delete(data);
            RELLX_LOG("Display Server CleanUp Completed!")
        };
        Rellx::Servers::WindowInstance* Rellx::Servers::DisplayServer::CreateWindowInstance() {
            Rellx::Servers::WindowInstance* ptr = nullptr;
            for (Rellx::Types::Int32 i = 0; i < MAX_WINDOWS; i++){
                if (windows[i])continue;
                ptr = Rellx::Memory::New<Rellx::Servers::WindowInstance>();
                if (ptr){
                    ptr->windowHanlder = Rellx::Memory::New<Rellx::Servers::WindowHandler>();
                    ptr->ID = i;
                    windows[i] = ptr;
                };
                break;
            };
            if (!ptr){
                RELLX_LOG_ERROR("Cant Create Window Instance!")
                return nullptr;
            };
            return ptr;
        };
        void Rellx::Servers::DisplayServer::DestroyWindowInstance(Rellx::Servers::WindowInstance* instance){
            if (!instance){
                RELLX_LOG_ERROR("Window Instance Is Invalid!!!")
                return;
            };
            if (instance->window)SDL_DestroyWindow(instance->window);
            windows[instance->ID] = nullptr;
            RELLX_LOG("Destroy Window Instance ID %d",instance->ID)
            Rellx::Memory::Delete(instance->windowHanlder);
            Rellx::Memory::Delete(instance);
        };
        void Rellx::Servers::DisplayServer::SetWindowSize(Rellx::Servers::WindowInstance* instance,const Rellx::Vector2i& size){
            if (!instance){
                RELLX_LOG_ERROR("Window Instance Is Invalid!!!")
                return;
            };
            instance->size = size;
        };
        Rellx::Vector2i Rellx::Servers::DisplayServer::GetWindowSize(Rellx::Servers::WindowInstance* instance) const {
            if (!instance){
                RELLX_LOG_ERROR("Window Instance Is Invalid!!!")
                return Rellx::Vector2i(0,0);
            };
            return instance->size;
        };


        void Rellx::Servers::DisplayServer::SetWindowTitle(Rellx::Servers::WindowInstance* instance,const Rellx::String& title){
            if (!instance){
                RELLX_LOG_ERROR("Window Instance Is Invalid!!!")
                return;
            };
            instance->title = title;
        };
        Rellx::String Rellx::Servers::DisplayServer::GetWindowTitle(Rellx::Servers::WindowInstance* instance) const{
            if (!instance){
                RELLX_LOG_ERROR("Window Instance Is Invalid!!!")
                return Rellx::String("");
            };
            return instance->title;
        };

        void Rellx::Servers::DisplayServer::SetVsyncMode(Rellx::VsyncsModes mode) noexcept{
            vsyncMode = mode;
            if (vsyncMode == Rellx::VsyncsModes::OFF){
                SDL_GL_SetSwapInterval(0);
                RELLX_LOG("Vsync Mode : OFF")
            }else if (vsyncMode == Rellx::VsyncsModes::ON){
                SDL_GL_SetSwapInterval(1);
                RELLX_LOG("Vsync Mode : ON")
            }else if (vsyncMode == Rellx::VsyncsModes::ADAPTIVE){
                SDL_GL_SetSwapInterval(-1);
                RELLX_LOG("Vsync Mode : ADAPTIVE")
            };
        };
        Rellx::VsyncsModes Rellx::Servers::DisplayServer::GetVsyncMode() const noexcept{return vsyncMode;};

        
        void Rellx::Servers::DisplayServer::SpawnWindow(Rellx::Servers::WindowInstance* instance){
            if (!instance){
                RELLX_LOG_ERROR("Window Instance Is Invalid!!!")
                return;
            };
            
            instance->window = SDL_CreateWindow(instance->title.c_str(),instance->size.x,instance->size.y,SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
            if (instance->window){
                SDL_SetWindowPosition(instance->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
                instance->windowHanlder->ptr = static_cast<void*>(instance->window);
                instance->shouldClose = false;
                RELLX_LOG("Spawn Window ID %d",instance->ID)
            }else{
                RELLX_LOG_ERROR("Cant Spawn Window ID %d",instance->ID)
                RELLX_LOG_ERROR(SDL_GetError())
            };
        };
        bool Rellx::Servers::DisplayServer::WindowShouldClose(Rellx::Servers::WindowInstance* instance) const {
            if (!instance){
                RELLX_LOG_ERROR("Window Instance Is Invalid!!!")
                return false;
            };
            return instance->shouldClose;
        };
        WindowHandler* Rellx::Servers::DisplayServer::GetWindowHandler(Rellx::Servers::WindowInstance* instance) const{
            if (instance) return instance->windowHanlder;
            return nullptr;
        };
    };
};