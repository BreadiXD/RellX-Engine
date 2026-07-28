#include "Servers/InputServer.hpp"
#include "Core/Utility.hpp"
#include "SDL3/SDL.h"
namespace Rellx{
    namespace Servers{
        struct InputServerData{
            
        };
        void Rellx::Servers::InputServer::Initialize(){
            RELLX_LOG("Input Server Initializing...")
            data = Rellx::Memory::New<Rellx::Servers::InputServerData>();
            RELLX_LOG("Input Server Initialized")
        };
        void Rellx::Servers::InputServer::BeginFrame(){
            
        };
        void Rellx::Servers::InputServer::EndFrame(){

        };
        void Rellx::Servers::InputServer::CleanUp(){

        };
    };
};