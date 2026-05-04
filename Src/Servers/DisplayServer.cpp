#include "Servers/DisplayServer.hpp"
#include "Core/Utility.hpp"
#include "SDL3/SDL.h"
namespace Rellx{
    namespace Servers{
        struct WindowInstance{
            SDL_Window* window = nullptr;
            Rellx::Types::Int32 ID = 0;
            Rellx::Variants::Vector2i size;
            bool shouldClose = false;
        };
        struct DisplayServerData{
            SDL_Event event;
        };
        void Rellx::Servers::DisplayServer::Initalize(){
            RELLX_LOG("Display Server Initalizing...")
            if (SDL_InitSubSystem(SDL_INIT_VIDEO)){
                for (Rellx::Types::Int32 i = 0; i < MAX_WINDOWS; i++)windows[i] = nullptr;
                data = Rellx::Memory::New<Rellx::Servers::DisplayServerData>();
                RELLX_LOG("Display Server Initalized")
            }else{
                RELLX_LOG_ERROR("Error Initalize DisplayServer!")
                RELLX_LOG_ERROR(SDL_GetError())
            };
        };
        void Rellx::Servers::DisplayServer::Update(){
            while(SDL_PollEvent(&data->event)){
                if (data->event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED){
                    for (Rellx::Types::Int32 i = 0; i < MAX_WINDOWS; i++){
                        if (!windows[i])continue;
                        if (SDL_GetWindowID(windows[i]->window) == data->event.window.windowID){
                            RELLX_LOG("Window Should Close ID %d",i)
                            windows[i]->shouldClose = true;                        
                        };    
                    };
                    break;
                };
            };
        };
        void Rellx::Servers::DisplayServer::CleanUp(){
            RELLX_LOG("Display Server CleanUp...")
            for (Rellx::Types::Int32 i = 0; i < MAX_WINDOWS; i++){
                if (windows[i]) DestroyWindowInstance(windows[i]);
            };
            Rellx::Memory::Delete(data);
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
            RELLX_LOG("Display Server CleanUp Completed!")
        };
        Rellx::Servers::WindowInstance* Rellx::Servers::DisplayServer::CreateWindowInstance(){
            Rellx::Servers::WindowInstance* ptr;
            for (Rellx::Types::Int32 i = 0; i < MAX_WINDOWS; i++){
                if (windows[i])continue;
                ptr = Rellx::Memory::New<Rellx::Servers::WindowInstance>();
                if (ptr){
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
            if (instance){
                if (instance->window)SDL_DestroyWindow(instance->window);
                windows[instance->ID] = nullptr;
                Rellx::Memory::Delete(instance);
            };
        };
        void Rellx::Servers::DisplayServer::SetWindowSize(Rellx::Servers::WindowInstance* instance,const Rellx::Variants::Vector2i& size){
            if (instance){
                instance->size = size;
            };
        };
        Rellx::Variants::Vector2i Rellx::Servers::DisplayServer::GetWindowSize(Rellx::Servers::WindowInstance* instance) const {
            return instance->size;
        };
        void Rellx::Servers::DisplayServer::SpawnWindow(Rellx::Servers::WindowInstance* instance){
            instance->window = SDL_CreateWindow("",instance->size.x,instance->size.y,0);
            if (instance->window){
                instance->shouldClose = false;
                RELLX_LOG("Spawn Winodw ID %d",instance->ID)
            }else{
                RELLX_LOG_ERROR("Cant Spawn Winodw ID %d",instance->ID)
                RELLX_LOG_ERROR(SDL_GetError())
            };
        };
        bool Rellx::Servers::DisplayServer::WindowShouldClose(Rellx::Servers::WindowInstance* instance) const {
            return instance->shouldClose;
        };
    };
};